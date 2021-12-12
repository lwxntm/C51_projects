#include "main.h"

#include "UART1_AutoDownload.h"
#include "LCD1602.h"

void main()
{
  uint8_t c = '0';
  DelayXms_AT44983(100);             //等待内部电路稳定
  Uart_autoDownload_Init();          // 使能串口1@2400bps接收到0x7F之后，自动进入ISP代码区
  init_all_gpio_to_std8051_status(); //所有的GPIO初始化为弱上拉模式
  DelayXms_AT44983(50);
  LCD_Init();
  LCD_showString(2, 5, "Hello, world");
  LCD_ShowInt(1, 1, 96, 3);
  P7M1 |= 1 << 3;
  P7M0 |= 1 << 3; // DS18B20 对应的IO口配置为开漏输出

  while (1)
  {
    DelayXms_AT44983(50);
  }
}
