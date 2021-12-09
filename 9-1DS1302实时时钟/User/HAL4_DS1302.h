/*
// DS1302 驱动模块，注意：VCC必须接3V3,如果接5V可能导致读出的都是FF和FE
*/



#ifndef __HAL4_DS1302_H__
#define __HAL4_DS1302_H__

// include
#include "STC8A8K64D4.H"
#include <intrins.h>
#include "TYPEDEF.h"
// end include

//define sbit
sbit DS1302_CE = P7 ^ 4;
sbit DS1302_IO = P7 ^ 5;
sbit DS1302_CLK = P7 ^ 6;
//end define

/**
  * @brief  DS1302初始化，注意：VCC必须接3V3,如果接5V可能导致读出的都是FF和FE
  * @param  无
  * @retval 无
  */                                                                                                                                                                                                                                        
void DS1302_Init()
{
    DS1302_CE = 0;
    DS1302_CLK = 0;
    DS1302_IO=0;
}

/**
  * @brief  DS1302操作时，为防止操作频率过快，空置大约2.7us @ 44.2368 MHz
  * @param  无
  * @retval 无
  */
void __DS1302_command_delay(void)
{
    volatile i = 10;
    while (--i)
        ;
}

void DS1302_WriteByte(uint8_t Command, uint8_t Writed_Data)
{
    uint8_t i;
    DS1302_CE = 1;
    for (i = 0; i < 8; i++)
    {
        DS1302_IO = Command & (1 << i);
        __DS1302_command_delay();
        DS1302_CLK = 1;
        __DS1302_command_delay();
        DS1302_CLK = 0;
        __DS1302_command_delay();
    }
    for (i = 0; i < 8; i++)
    {
        DS1302_IO = Writed_Data & (1 << i);
        __DS1302_command_delay();
        DS1302_CLK = 1;
        __DS1302_command_delay();
        DS1302_CLK = 0;
        __DS1302_command_delay();
    }
    DS1302_CE = 0;
}


unsigned char DS1302_ReadByte(unsigned char Command)
{
	unsigned char i,Data=0x00;
    __DS1302_command_delay();

    DS1302_CE=0; //这条很重要
	DS1302_CLK=0; //先将SCLK置低电平,确保写数居前SCLK被拉低
	Command|=0x01;	//将指令转换为读指令
	DS1302_CE=1;
	for(i=0;i<8;i++)
	{
        if (Command&(0x01<<i))
        {
            DS1302_IO=1;
            /* code */
        }else{
            DS1302_IO=0;
        }
        __DS1302_command_delay();
		DS1302_CLK=0;
        __DS1302_command_delay();
		DS1302_CLK=1;
        __DS1302_command_delay();
        __DS1302_command_delay();
        __DS1302_command_delay();
	}
  DS1302_IO=1; //锁存1 再读取
    __DS1302_command_delay();
    __DS1302_command_delay();
	for(i=0;i<8;i++)
	{
		DS1302_CLK=1;
        __DS1302_command_delay();
		DS1302_CLK=0;
        __DS1302_command_delay();

		if(DS1302_IO)Data|=(0x01<<i);
        __DS1302_command_delay();
	}
	DS1302_CE=0;
   // P1M0|=1<<3;
  //  P1M1&=~(1<<3);   // IO 推挽输出
	DS1302_IO=0;	//读取后将IO设置为0，否则读出的数据会出错
	return Data;
}

#endif