#ifndef __DS18B20_H__
#define __DS18B20_H__

#include <STC8A8K64D4.H>
#include "TYPEDEF.h"
#include <intrins.h>

sbit DS18B20_DQ = P7 ^ 3;

uint8_t DS18B20_Init()
{
	uint8_t AckBit;
	unsigned char i, j;

	DS18B20_DQ = 1;
	i = 223;
	while (--i)
		; //先给高电平，等一会再给低电平，让总线产生下降沿
	DS18B20_DQ = 0;
	i = 30;
	j = 51;
	do
	{
		while (--j)
			;
	} while (--i); //Delay500us()		//@44.983MHz
	DS18B20_DQ = 1;
	i = 5;
	j = 20;
	do
	{
		while (--j)
			;
	} while (--i); //Delay70us()		//@44.983MHz
	AckBit = DS18B20_DQ;
	i = 30;
	j = 51;
	do
	{
		while (--j)
			;
	} while (--i); //Delay500us()		//@44.983MHz
	return AckBit;
}

void DS18B20_SendBit(uint8_t bi)
{
	unsigned char i, j;
	DS18B20_DQ = 0;
	i = 148;
	while (--i)
		; //Delay10us()		//@44.983MHz
	DS18B20_DQ = bi;

	i = 4;
	j = 51;
	do
	{
		while (--j)
			;
	} while (--i); //Delay55us()		//@44.983MHz

	DS18B20_DQ = 1; // 释放总线
}

uint8_t DS18B20_ReceiveBit()
{
	//接收一位：主机将总线拉低1~15us，然后释放总线，并在拉低后15us内读取总线电平（尽量贴近15us的末尾），
	//读取为低电平则为接收0，读取为高电平则为接收1 ，整个时间片应大于60us
	uint8_t Bi;
	unsigned char i, j;

	DS18B20_DQ = 0;

	i = 73;
	while (--i)
		; // Delay5us()		//@44.983MHz
	DS18B20_DQ = 1;
	i = 73;
	while (--i)
		; // Delay5us()		//@44.983MHz
	Bi = DS18B20_DQ;
	i = 4;
	j = 51;
	do
	{
		while (--j)
			;
	} while (--i); //Delay55us()		//@44.983MHz
	return Bi;
}

void DS18B20_SendByte(uint8_t Byt)
{
	uint8_t i;
	for (i = 0; i < 8; i++)
	{
		DS18B20_SendBit(Byt & (1 << i));
		/* code */
	}
}

uint8_t DS18B20_ReceiveByte()
{
	uint8_t Dat = 0;
	uint8_t i;
	for (i = 0; i < 8; i++)
	{
		if (DS18B20_ReceiveBit())
			Dat |= (1 << i);
	}
	return Dat;
}

/**
  * @brief  DS18B20更新内部温度传感器的数据
  * @param  无
  * @retval 无
  */
void DS18B20_ConvertT()
{
	DS18B20_Init();
	DS18B20_SendByte(0xcc); //跳过ROM指令
	DS18B20_SendByte(0x44); //更新温度指令
}

/**
  * @brief  DS18B20获取温度的函数
  * @param  无
  * @retval 返回的是温度的16倍，请自行除以16！
  */
int16_t DS18B20_GetT()
{
	uint8_t TLSB, TMSB;
	int16_t Temp;

	DS18B20_Init();
	DS18B20_SendByte(0xcc); //跳过ROM指令
	DS18B20_SendByte(0xbe); //读取寄存器指令
	TLSB = DS18B20_ReceiveByte();
	TMSB = DS18B20_ReceiveByte();
	Temp = (TMSB << 8) | TLSB;
	return Temp;
}

#endif