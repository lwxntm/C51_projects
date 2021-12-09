#ifndef __Buzzer_H__
#define __Buzzer_H__

#include "TYPEDEF.h"
#include <STC8A8K64D4.H>


// 蜂鸣器的端口
sbit Buzzer = P4 ^ 2;

void Buzzer_Delay500us()		//@44.2368MHz
{
	unsigned char i, j;

	i = 29;
	j = 183;
	do
	{
		while (--j);
	} while (--i);
}

/**
  * @brief  蜂鸣器发声函数
  * @param  xms 蜂鸣器发声的时长
  * @retval 无
  */
void Buzzer_xms(uint16_t xms){
    uint16_t i=0;
     for (i = 0; i < xms; i++)
      {
        Buzzer = ~Buzzer;
        Buzzer_Delay500us();
      }
}

#endif