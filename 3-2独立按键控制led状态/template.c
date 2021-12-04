#include "STC8A8K64D4.h"

#include "alib.h"

#include <stdio.h>





void main()
{
  init_all_gpio_to_std8051_status();
   Delay_ms(20); //要加上这一句，不然可能即使给P06高电平灯也会亮
  P06=1;
  while (1)
  {
      if (P62==0)
      {
          Delay_ms(20);
          while (P62==0);
          Delay_ms(20);
          P06=~P06;
      }
  }
}
