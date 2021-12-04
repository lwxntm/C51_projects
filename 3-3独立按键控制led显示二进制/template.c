#include "STC8A8K64D4.h"

#include "alib.h"

#include <stdio.h>

uint8_t status_count = 0;
uint8_t modifyed = 1;

void main()
{
  init_all_gpio_to_std8051_status();
  Delay_ms(20); //要加上这一句，不然可能即使给P06高电平灯也会亮
  P06 = 1;
  while (1)
  {
    if (P62 == 0)
    {
      Delay_ms(20);
      while (P62 == 0)
        ;
      Delay_ms(20);
      status_count++;
      modifyed = 1;
    }
    if (modifyed)
    {
      P07 = (status_count & (1 << 0))==0?1:0;
      P06 = (status_count & (1 << 1))==0?1:0;
      P05 = (status_count & (1 << 2))==0?1:0;
      modifyed = 0;
    }
  }
}
