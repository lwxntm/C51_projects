#include "main.h"
#include "LCD1602.h"
#include "IndivBtn.h"
#include "AT24C02.h"
#include "DS18B20.h"

int16_t T;
void main()
{
  DelayXms_AT44983(50); //等待内部电路稳定
  init_all_gpio_to_std8051_status();
  LCD_Init();
  DelayXms_AT44983(50);

  P7M1 |= 1 << 3;
  P7M0 |= 1 << 3; // DS18B20 对应的IO口配置为开漏输出

  while (1)
  {
    DS18B20_ConvertT();
    DelayXms_AT44983(50);
    T = DS18B20_GetT();
    LCD_ShowBinNum(1, 1, T, 16); //在第一行显示读出来的原始值
    LCD_ShowString(2, 1, "TEMP:");
    if (T < 0)
    {
      LCD_ShowChar(2, 8, '-');
      T = -T;
    }
    else
      LCD_ShowChar(2, 8, '+');
    LCD_ShowNum(2, 9, T / 16, 3); //显示温度的整数部分
    LCD_ShowChar(2, 12, '.');
    LCD_ShowNum(2, 13, (uint32_t)((T / 16.0) * 10000) % 10000, 4); //显示温度的小数部分
  }
}
