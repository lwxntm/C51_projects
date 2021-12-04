#include "STC8A8K64D4.h"

#include "alib.h"
#include <stdio.h>

sbit outp = P3 ^ 1;
//sbit lR = P0 ^ 5;
//sbit lG = P0 ^ 6;
//sbit lB = P0 ^ 7;





void main()
{
  P0M0 = 0x00;
  P0M1 = 0x00; // P3.1输出模式
  P6M0 = 0x00;
  P6M1 = 0x00; // P3.1输出模式
 UART_SENDCHAR_AT_P15_INIT();
  while (1)
  {
    
    UART_SENDCHAR_AT_P15(0x0f);
  }
}
