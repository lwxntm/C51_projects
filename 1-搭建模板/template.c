#include "STC8A8K64D4.h"
#include <intrins.h>
#include "alib.h"
sbit outp = P3 ^ 1;
//sbit lR = P0 ^ 5;
//sbit lG = P0 ^ 6;
//sbit lB = P0 ^ 7;
void Delay1ms()		//@12.000MHz
{
	unsigned char i, j;

	i = 16;
	j = 147;
	do
	{
		while (--j);
	} while (--i);
}




void main()
{
  P0M0 |= 1 << 5;
  P0M1 &= ~(1 << 5); // P3.1Êä³öÄ£Ê½
  while (1)
  {
    P0|=1<<5;
    Delay1ms();
    P0&=~(1<<5);
    Delay1ms();
    

  }
}
