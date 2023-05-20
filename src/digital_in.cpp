#include <digital_in.h>
#include <avr/io.h>

Digital_in::Digital_in(int button_pin)
{
    SWITCH_PIN = (1 << button_pin);
}

void Digital_in::init()
{
    DDRD &= ~SWITCH_PIN; // Configure port D pin as a n input
    PORTD |= SWITCH_PIN; // Enable pull-up resistor 
}

uint8_t Digital_in::switch_state() //Reads if the button is pressed
{
    return (PIND & (1<<0));
}

bool Digital_in::is_hi()
{
    return PIND &  SWITCH_PIN;
}

bool Digital_in::is_lo()
{
    return !is_hi();
}