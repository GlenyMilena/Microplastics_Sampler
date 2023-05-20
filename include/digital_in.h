#include <stdint.h>
#include <avr/io.h>

class Digital_in
{
private:
    bool state;
    uint8_t SWITCH_PIN;

public: 

    Digital_in(int button_pin);
    void init();
    uint8_t switch_state();
    bool is_lo();
    bool is_hi(); 
};

