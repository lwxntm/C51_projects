
#include "STC8A8K64D4.h"

#include "alib.h"
#include "LCD1602.h"
#include <stdio.h>
#include "MatrixKey.h"

uint8_t main_key_num = 0;

void main()
{

  init_all_gpio_to_std8051_status();
  LCD_Init();

  while (1)
  {
    main_key_num = Get_key_num();
    if (main_key_num)
    {
      LCD_ShowNum(1, 1, main_key_num, 2);
      main_key_num = 0;
      /* code */
    }
  }
}
