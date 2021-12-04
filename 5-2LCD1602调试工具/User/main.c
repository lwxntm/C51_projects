
#include "STC8A8K64D4.h"

#include "alib.h"
#include "LCD1602.h"
#include <stdio.h>

void main()
{
  uint16_t count = 0;

  init_all_gpio_to_std8051_status();
  LCD_Init();

  while (1)
  {
    LCD_ShowNum(1, 1, count, 5);
    count++;
    Delay_ms(1000);
    /* code */
  }
}
