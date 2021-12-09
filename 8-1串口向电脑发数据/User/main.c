#include "main.h"
#include "stdio.h"
#include "UART1.h"
#include "LCD1602.h"

char buf[20];
uint8_t cnt=0;
void main()
{
  init_all_gpio_to_std8051_status();
  Uart1_Init__115200__44MHz2368__Send_Rev_both();
  LCD_Init();

  while (1)
  {
    LCD_ShowString(1,1,buf);
  }
}

void UART1_Routine() interrupt 4{
  
  if (RI==1)
  {
    buf[cnt++]=SBUF;
    RI=0;
    /* code */
  }
  
}