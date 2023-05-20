#include <stdint.h>
#include <avr/io.h>
#include <digital_out.h>

Digital_out::Digital_out(int pin_number)
{
    pinMask = (1 << pin_number);
}

void Digital_out::init()
{
    DDRD |= pinMask;
}
  
void Digital_out::set_hi()
{
    PORTD |= pinMask;
}
  
void Digital_out::set_lo()
{
    PORTD = PORTD & ~pinMask;
}
  
void Digital_out::toggle()
{
    PORTD = PORTD ^pinMask;
}