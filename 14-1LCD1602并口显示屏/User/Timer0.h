#ifndef __TIMER0_H__
#define __TIMER0_H__

#include "STC8A8K64D4.h"

/**
  * @brief  Timer0初始化函数 45MHz, 12T 1ms 计数
  * @param  无
  * @retval 无
  */
void Timer0_Init() //1毫秒@44.2368MHz
{
  AUXR &= 0x7F; //定时器时钟12T模式
  //  TMOD = 0x01;       // 0000 0001 用作定时器，16位不自动重载模式，见手册P312
  TMOD &= 0xF0; //设置定时器模式
  TMOD |= 0x01; //设置定时器模式
  TF0 = 0;      //当计数器溢出时，硬件将该位置1
  TR0 = 1;      //允许计数
  ET0 = 1;      //允许T0中断，手册P232
  EA = 1;       //总中断开关，手册P232
  PT0 = 0;      // 定时器0中断优先级控制位  手册241

  TL0 = 63625%256; //设置定时初始值
  TH0 = 63625/256; //设置定时初始值
}

//
/* 定时器中断模板


void Timer0_Rountine() interrupt 1
{
  static uint16_t T0Count = 0;
  TH0 = 64536 / 256; //计数寄存器，累加1000次后溢出 (65535-64535 = 1000)
  TL0 = 64536 % 256;
  T0Count++;
  if (T0Count >= 500)
  {
    T0Count = 0;
    P05 = ~P05;
  }
}


*/

#endif
