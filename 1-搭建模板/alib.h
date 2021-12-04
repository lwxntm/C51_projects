#include "STC8A8K64D4.h"

enum pinMode_enum
{
    OUTPUT = 0,
    INPUT,

};

void pinModeOutput(uint8_t pin_port, uint8_t pin_num)
{
}

//5 ticks 大约 1us  在44.2368MHz
void delay_some_ticks(volatile uint8_t ticks)
{
    while (ticks--)
        ;
}

void delay_uint16_ticks(volatile uint16_t ticks){
    while (ticks--)
        ;
}
#define delay_115200Hz delay_uint16_ticks(36)

void delay_ms(volatile uint32_t mss)
{
    while (mss--)
    {
        volatile i = 832;
        while (i--)
        {
            delay_some_ticks(5);
        }
    }
}