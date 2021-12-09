#ifndef __IIC_H__
#define __IIC_H__

#include <STC8A8K64D4.H>
#include "TYPEDEF.h"

sbit IIC_SCL = P1 ^ 5;
sbit IIC_SDA = P1 ^ 4;

/**
  * @brief  IIC通信等待200US
  * @param  无
  * @retval 无
  */
void IIC_Delay200us() //@44.242MHz
{
    unsigned char i, j;

    i = 12;
    j = 123;
    do
    {
        while (--j)
            ;
    } while (--i);
}

/**
  * @brief  IIC通信起始
  * @param  无
  * @retval 无
  */
void IIC_Start()
{
    //若SCL和SDA都是高电平，前两条语句不做任何事情。若SCL此时为低电平，则先把SDA拉高再把SCL拉高，然后再发送起始命令
    IIC_SDA = 1;
    IIC_Delay200us();
    IIC_SCL = 1;
    IIC_Delay200us();
    // 发送起始位,指SCL高电平期间，SDA从高电平切换到低电平
    IIC_SDA = 0;
    IIC_Delay200us();
    //为了适配后续其他的操作，发送完起始位之后将SCL拉低
    IIC_SCL = 0;
    IIC_Delay200us();
}

/**
  * @brief  IIC通信结束
  * @param  无
  * @retval 无
  */
void IIC_Stop()
{
    //终止条件：SCL高电平期间，SDA从低电平切换到高电平
    IIC_SDA = 0; //先让SDA呆在低电平
    IIC_SCL = 1; //拉高SCL
    IIC_SDA = 1; //SDA从低电平切换到高电平
}

/**
  * @brief  IIC通信发送字节
  * @param  Byte 要发送的字节
  * @retval 无
  */
void IIC_SendByte(uint8_t Byte)
{
    /*
    发送一个字节：SCL低电平期间，主机将数据位依次放到SDA线上（高位在前），然后拉高SCL.
    从机将在SCL高电平期间读取数据位，所以SCL高电平期间SDA不允许有数据变化，依次循环上述过程8次，即可发送一个字节
    */
    uint8_t i;
    for (i = 0; i < 8; i++)
    {
        IIC_SDA = (Byte & (0x80 >> i)); //高位在前
        IIC_SCL = 1;
        IIC_Delay200us();
        IIC_SCL = 0;
        IIC_Delay200us();
    }
}

/**
  * @brief  IIC通信接收字节
  * @param  无
  * @retval 要接收的字节
  */
uint8_t IIC_ReceiveByte()
{
    /*
    接收一个字节：SCL低电平期间，从机将数据位依次放到SDA线上（高位在前）
    然后拉高SCL，主机将在SCL高电平期间读取数据位，所以SCL高电平期间SDA不允许有数据变化，
    依次循环上述过程8次，即可接收一个字节（主机在接收之前，需要释放SDA）
    */
    uint8_t i = 0, Byte = 0;
    IIC_SDA = 1; // 释放SDA

    for (i = 0; i < 8; i++)
    {
        IIC_SCL = 1; //拉高SCL，主机将在SCL高电平期间读取数据位
        IIC_Delay200us();
        if (IIC_SDA)
            Byte |= (0x80 >> i);
        IIC_SCL = 0;
        IIC_Delay200us();
    }
    return Byte;
}

/**
  * @brief  IIC通信发送应答
  * @param  AckBit 要发送的应答
  * @retval 无
  */
void IIC_SendAck(uint8_t AckBit)
{
    /*
    发送应答：在接收完一个字节之后，主机在下一个时钟发送一位数据，数据0表示应答，数据1表示非应答
    */
    IIC_SDA = AckBit;
    //拉高再拉低
    IIC_SCL = 1;
    IIC_Delay200us();
    IIC_SCL = 0;
    IIC_Delay200us();
}

/**
  * @brief  IIC通信接收应答
  * @param  无
  * @retval 收到的应答
  */
uint8_t IIC_ReceiveAck()
{
    /*
    接收应答：在发送完一个字节之后，主机在下一个时钟接收一位数据，判断从机是否应答，
    数据0表示应答，数据1表示非应答（主机在接收之前，需要释放SDA）
    */
    uint8_t AckBit = 0;
    IIC_SDA = 1; //释放SDA
    IIC_SCL = 1;
    IIC_Delay200us();
    AckBit = IIC_SDA; //读取应答
    IIC_SCL = 0;
    IIC_Delay200us();
}

#endif