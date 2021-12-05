#include "main.h"

#include "Timer0.h"
#include "IndivBtn.h"
#include "LCD1602.h"

uint8_t HR = 23;
uint8_t MN = 58;
uint8_t SE = 50;

void Timer0_Rountine() interrupt 1
{
  static uint16_t T0Count = 0;
  TL0 = 0x5A; //设置定时初始值
  TH0 = 0xF1; //设置定时初始值
  T0Count++;
  if (T0Count >= 1000)
  {
    T0Count = 0;

    SE++;
    if (SE==60)
    {
      SE=0;
      MN++;
      if (MN==60)
      {
        MN=0;
        HR++;
        if (HR==24)
        {
          HR=0;
          /* code */
        }
        
        /* code */
      }
      
      /* code */
    }
    
  }
}



void main()
{
  init_all_gpio_to_std8051_status();
  Timer0_Init();
  LCD_Init();

  while (1)
  {
    LCD_ShowString(1, 1, "Clock:");
    LCD_ShowNum(2, 1, HR, 2);
    LCD_ShowChar(2, 3, ':');
    LCD_ShowNum(2, 4, MN, 2);
    LCD_ShowChar(2, 6, ':');
    LCD_ShowNum(2, 7, SE, 2);
  }
}
