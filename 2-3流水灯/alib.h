
#include "STC8A8K64D4.h"
#include <intrins.h>
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

void Delay208us()		//@33.1776MHz
{
	unsigned char i, j;

	i = 9;
	j = 244;
	do
	{
		while (--j);
	} while (--i);
}


void UART_SENDCHAR_AT_P15_INIT(){
    P1M0=0xff;
    P1M1=0x00;
    
}

uint8_t i = 0;
//uint8_t c=0x0f;
void UART_SENDCHAR_AT_P15(uint8_t c){
    Delay208us();
    P15=0; //start bit
    Delay208us();
    
    

    for (i = 0; i < 8; ++i) {
        if (c & (1 << i))
            P15=1;
        else
             P15=0;
        Delay208us();
    }
     P15=1; //stop bit
    Delay208us();
}