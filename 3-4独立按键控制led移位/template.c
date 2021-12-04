#include "STC8A8K64D4.h"

#include "alib.h"

#include <stdio.h>

uint8_t status_count = 5;
uint8_t modifyed = 1;

void main()
{
  init_all_gpio_to_std8051_status();
  Delay_ms(20); //硬件防抖
  while (1)
  {
    if (P62 == 0)
    {
      Delay_ms(20);
      while (P62 == 0)
        ;
      Delay_ms(20);
      status_count++;
      if (status_count > 7)
      {
        status_count = 5;
        /* code */
      }

      modifyed = 1;
    }
    if (P61 == 0)
    {
      Delay_ms(20);
      while (P61 == 0)
        ;
      Delay_ms(20);
      status_count--;
      if (status_count < 5)
      {
        status_count = 7;
        /* code */
      }

      modifyed = 1;
    }
    
    if (modifyed)
    {
      P0 = ~(0x01 << status_count);
      modifyed = 0;
    }
    if (P60 == 0)  // 按下P60之后，关闭LED灯
    {
       Delay_ms(20);
      while (P60 == 0)
        ;
      Delay_ms(20);
      P0=0xff;
    }
  }
}
