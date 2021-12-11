#include "main.h"
#include "LCD1602.h"
#include "IndivBtn.h"
#include "AT24C02.h"

uint8_t Data = 0;

void main()
{
  uint8_t str_ptr = 0;

  uint16_t i = 0;
  uint8_t key = 0;
  DelayXms_AT44983(50); //等待内部电路稳定
  init_all_gpio_to_std8051_status();
  LCD_Init();

  DelayXms_AT44983(50);
  P1M1 |= 1 << 4;
  P1M1 |= 1 << 5;

  P1M0 |= 1 << 4;
  P1M0 |= 1 << 5;

  LCD_ShowString(1, 1, "1++ 2-- 3LOAD");

  while (1)
  {
    key = Get_onboard_key_num();
    if (key == 1)
    {
      // Data++;
      // AT24C02_Write_Byte(1, Data);
      AT24C02_Write_Multi_Bytes(0, 10, "fuckYYYY");
    }
    else if (key == 2)
    {
      Data--;
      AT24C02_Write_Byte(1, Data);
      /* code */
    }
    else if (key == 3)
    {
      for (str_ptr = 0; str_ptr < 8; str_ptr++)
      {
        LCD_ShowChar(2, str_ptr + 1, AT24C02_Read_byte(str_ptr));
      }
    }
  }
}
