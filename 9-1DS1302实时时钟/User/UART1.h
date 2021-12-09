#ifndef __UART1_H__
#define __UART1_H__

#include "STC8A8K64D4.H"
#include "TYPEDEF.h"

/**
  * @brief  串口1初始化函数，使用9600波特率，工作在44.2368MHz
  * @param  无
  * @retval 无
  */
void UART1_Init_9600___44_2368MHz()
{
  SCON = 0x40;
  PCON |= 0x80; ///波特率倍速
  AUXR &= 0xBF; //定时器时钟12T模式
  AUXR &= 0xFE; //串口1选择定时器1为波特率发生器
  TMOD &= 0x0F; //设置定时器模式
  TMOD |= 0x20; //设置定时器模式
  TL1 = 0xE8;   //设置定时初始值
  TH1 = 0xE8;   //设置定时重载值
  ET1 = 0;      //禁止定时器%d中断
  TR1 = 1;      //定时器1开始计时
}

/**
  * @brief  串口1初始化函数，使用115200波特率，工作在44.2368MHz
  * @param  无
  * @retval 无
  */
void Uart1_Init__115200__44MHz2368__Send_only(void)		//115200bps@44.2368MHz
{
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x40;		//定时器时钟1T模式
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0xA0;		//设置定时初始值
	TH1 = 0xFF;		//设置定时初始值
	ET1 = 0;		//禁止定时器%d中断
	TR1 = 1;		//定时器1开始计时
}

void UartInit__9600__5MHz5296(void)		//9600bps@5.5296MHz
{
	SCON = 0x50;		//8位数据,可变波特率
	AUXR &= 0xBF;		//定时器时钟12T模式
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0xF4;		//设置定时初始值
	TH1 = 0xFF;		//设置定时初始值
	ET1 = 0;		//禁止定时器%d中断
	TR1 = 1;		//定时器1开始计时
}


/**
  * @brief  串口1初始化函数，使用115200波特率，工作在44.2368MHz
  * @param  无
  * @retval 无
  */
void Uart1_Init__115200__44MHz2368__Send_Rev_both(void)		//115200bps@44.2368MHz
{
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x40;		//定时器时钟1T模式
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0xA0;		//设置定时初始值
	TH1 = 0xFF;		//设置定时初始值
	ET1 = 0;		//禁止定时器%d中断
	TR1 = 1;		//定时器1开始计时
    ES=1;
    EA=1;  // 手册P232;
}


/**
  * @brief  串口1 发送一个字节
  * @param  无
  * @retval 无
  */
void UART1_SendChar(char c)
{
  SBUF = c;
  while (TI == 0)
    ;
  TI = 0;
}

/**
  * @brief  串口1 发送一个字符串
  * @param  无
  * @retval 无
  */
void UART1_SendStr(const char *s)
{
  uint8_t i = 0;
  while (s[i])
  {
    UART1_SendChar(s[i++]);
  }
}

#endif