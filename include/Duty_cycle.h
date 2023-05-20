#include <avr/io.h>
#include <avr/interrupt.h>

class duty_cycle
{
    public:
        float change_duty_cycle(float prev_duty);
};
