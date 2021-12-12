#ifndef __UART1AD_H__
#define __UART1AD_H__

#include "STC8A8K64D4.H"
#include "TYPEDEF.h"
void Uart_autoDownload_Init(void) //2400bps@44.983MHz
{
  SCON = 0x50;  //8位数据,可变波特率
  AUXR &= 0xBF; //定时器时钟12T模式
  AUXR &= 0xFE; //串口1选择定时器1为波特率发生器
  TMOD &= 0x0F; //设置定时器模式
  TL1 = 0x7A;   //设置定时初始值
  TH1 = 0xFE;   //设置定时初始值
  ET1 = 0;      //禁止定时器%d中断
  TR1 = 1;      //定时器1开始计时
  ES = 1;
  EA = 1; // 
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


#endif