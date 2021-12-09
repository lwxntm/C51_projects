#include "main.h"
#include "LCD1602.h"
#include "IndivBtn.h"

void main()
{
  uint16_t i = 0;
  uint8_t key = 0;
  init_all_gpio_to_std8051_status();
  LCD_Init();

  Delay_ms(10);
  LCD_ShowString(1, 1, "Hello, world");

  while (1)
  {
    key = Get_onboard_key_num();
    if (key)
    {
      LCD_ShowNum(2, 1, key, 1);
    }
  }
}
