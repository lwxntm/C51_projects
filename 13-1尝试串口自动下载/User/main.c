#include "main.h"
#include "LCD1602.h"
#include "IndivBtn.h"
#include "AT24C02.h"
#include "DS18B20.h"
#include "UART1.h"
int16_t T;
void main()
{
  DelayXms_AT44983(100);             //等待内部电路稳定
  Uart_autoDownload_Init();          // 使能串口1@2400bps接收到0x7F之后，自动进入ISP代码区
  init_all_gpio_to_std8051_status(); //所有的GPIO初始化为弱上拉模式
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

void UART1_AutoDownload_Routine() interrupt 4
{
  static uint8_t AutoDownloadCount = 0;

  if (RI)
  {
    RI = 0;
    if (SBUF == 0x7f)
    {
      AutoDownloadCount++;
      if (AutoDownloadCount > 10)
        IAP_CONTR = 0x60; //软件复位，从系统ISP区执行代码
    }
    else
      AutoDownloadCount = 0;
  }
  if (TI)
    TI = 0;
}
