//Measure the volume of water that is beign sampled

#include <digital_out.h>
#include <digital_in.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <Arduino.h>

//Signals
Digital_out pump(5); //Defines pin D5 as output (pump signal)
Digital_in flow_sensor(2); //Defines pin D2 as input (flow sensor signal)
int drone = 3; 
boolean pump_state = false; 

//Variables 
double flowRate; //flow measurement
double waterVolume = 0.0; 
double SetPoint = 10.0; // 10 liters                                                                  
unsigned long currentTime = 0;
unsigned long lastTime = 0;
unsigned long pulse_freq=0; //flow sensor pulse frequency 

//Variables for pwm signal
unsigned long ontime = 0; 
unsigned long offtime = 0; 
unsigned long duty_cycle=0; 
float period = 0.0; 

ISR (INT0_vect)
{
  //Serial.println("pulses");
  pulse_freq++;
}

void setup()
{
  //Signals initialization
  Serial.begin(9600);
  pump.init();
  flow_sensor.init();

  pinMode(drone, INPUT);

  //enabling interrupt for flow sensor
  PORTD |= (1 << PORTD2); // enable pull-up resistor on PD2
  EICRA |= (1 << ISC00); // set INT0 to trigger on ANY logic change
  EIMSK |= (1 << INT0); // Turns on INT0
  sei(); // turn on interrupts

  //activating pump
  Serial.println("Pump off");
  pump.set_hi(); 
  //pump.set_lo(); 
  pump_state = false; 
}

void loop()
{
  //Reading duty cycle state
  ontime = pulseIn(drone,HIGH);

  offtime = pulseIn(drone, LOW);

  period = ontime+offtime;

  duty_cycle = (ontime/period)*100;

  //taking starting time
  currentTime = millis(); 
  lastTime =currentTime; 

  if(duty_cycle >= 65)
  {

    if(pump_state == false)
    {
      Serial.print("Pump ON");
      Serial.print('\n');

      //pump.set_hi();
      pump.set_lo();
      pump_state = true; 
    }
    currentTime = millis();

    //Reading every second
    if(currentTime >= lastTime + 1000)
    {
        lastTime = currentTime;
        if (waterVolume <= SetPoint)
        {
          // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
          flowRate = (pulse_freq /7.5)*0.9; 

          waterVolume += ((flowRate/60)*0.75); 

          pulse_freq = 0; 
        }
        else
        {
          Serial.println("Turn off PUMP");
          pump.set_lo();

          Serial.print("Sample collected");
          Serial.print(waterVolume, DEC); 
          Serial.print('\n');
        }
      }
  }
  else
  {
    if(pump_state == true)
    {
      pump.set_hi();
      pump_state = false; 
    
      Serial.print("Pump OFF");
      Serial.print('\n');
    }
  }
  delay(500);
}
