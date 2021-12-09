#include "main.h"
#include "LCD1602.h"
#include "HAL4_DS1302.h"
#include "UART1.h"
uint8_t second;

char buf[20]={0};

void main()
{
  init_all_gpio_to_std8051_status();
  LCD_Init();
  Delay_ms(10);
  Uart1_Init__115200__44MHz2368__Send_only();

  DS1302_Init();

  Delay_ms(100);
  while (1)
  {
    second = DS1302_ReadByte(0x81);
    UART1_SendChar(second);
    Delay_ms(1000);
  }
}
