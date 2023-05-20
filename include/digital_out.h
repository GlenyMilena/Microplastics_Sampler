#include <stdint.h>
#include <avr/io.h>

class Digital_out
{
  private:
  uint8_t pinMask;
 
  public:

  Digital_out(int pin_number);
  
  void init();
  
  void set_hi();
  
  void set_lo();

  void toggle();
  
};