#ifndef __SW_I2C_H__
#define __SW_I2C_H__

#include <STC8A8K64D4.H>
#include "TYPEDEF.h"
#include <intrins.h>

sbit SW_I2C_SCL = P1 ^ 5;
sbit SW_I2C_SDA = P1 ^ 4;

void Delay6us() //@44.983MHz
{
    unsigned char i;
    i = 88;
    while (--i)
        ;
}

void Delay18us() //@44.983MHz
{
    unsigned char i, j;

    _nop_();
    i = 2;
    j = 10;
    do
    {
        while (--j)
            ;
    } while (--i);
}

void Delay12us() //@44.983MHz
{
    unsigned char i;

    i = 178;
    while (--i)
        ;
}

void Delay160us() //@44.983MHz
{
    unsigned char i, j;

    i = 10;
    j = 86;
    do
    {
        while (--j)
            ;
    } while (--i);
}

void Delay2ms() //@44.983MHz
{
    unsigned char i, j;

    _nop_();
    i = 117;
    j = 212;
    do
    {
        while (--j)
            ;
    } while (--i);
}

/**
  * @brief  IIC通信start bit ：SCL 为高时，sda从高到低，等待大约6us后，scl也拉低
  * @param  无
  * @retval 无
  */
void SW_I2C_StartBit()
{
    SW_I2C_SDA = 1;
    Delay6us();
    SW_I2C_SCL = 1;
    Delay6us();
    SW_I2C_SDA = 0;
    Delay6us();
    SW_I2C_SCL = 0;
    Delay6us();
}
/**
  * @brief  IIC通信StopBit ：SCL 为高时，sda从低到高
  * @param  无
  * @retval 无
  */
void SW_I2C_StopBit()
{
    SW_I2C_SCL = 0;
    Delay6us();
    SW_I2C_SDA = 0;
    Delay6us();
    SW_I2C_SCL = 1;
    Delay6us();
    SW_I2C_SDA = 1;
    Delay6us();
}

/**
  * @brief  IIC通信发送从设备地址和读写位
  * @param  SlaveAddress 从机地址，应为7位，所以应小于0x80
  * @param    RW 写数据为 0， 读数据为 1
  * @retval 应答位，0表示应答，1 表示不应答
  */
uint8_t SW_I2C_SendSlaveAddress_and_RW_then_getAckBit(uint8_t SlaveAddress, uint8_t RW)
{
    uint8_t AckBit;
    uint8_t i;
    for (i = 0; i < 7; i++)
    {
        SW_I2C_SDA = (SlaveAddress & (0x40 >> i));
        Delay6us();
        SW_I2C_SCL = 1;
        Delay6us();
        SW_I2C_SCL = 0;
        Delay18us();
    }
    SW_I2C_SDA = RW;
    SW_I2C_SCL = 1;
    Delay6us();
    SW_I2C_SCL = 0;
    Delay6us();
    SW_I2C_SDA = 1; //释放sda
    Delay12us();
    SW_I2C_SCL = 1;
    Delay18us();
    AckBit = SW_I2C_SDA; //此时AckBit 应该为0，表示从机给与应答
    SW_I2C_SCL = 0;
    Delay6us();
    //地址位发送完成
    return AckBit;
}

/**
  * @brief  IIC通信发送一个字节的数据，然后获取应答
  * @param  Dat 要发送的数据
  * @retval 应答位，0表示应答，1 表示不应答
  */
uint8_t SW_I2C_SendByte_then_getAckBit(uint8_t Dat)
{
    uint8_t AckBit = 0;
    uint8_t i;
    for (i = 0; i < 8; i++)
    {
        SW_I2C_SDA = (Dat & (0x80 >> i));
        Delay6us();
        SW_I2C_SCL = 1;
        Delay6us();
        SW_I2C_SCL = 0;
        Delay18us();
    }
    SW_I2C_SDA = 1; //释放sda
    Delay12us();
    SW_I2C_SCL = 1;
    Delay18us();
    AckBit = SW_I2C_SDA; //此时AckBit 应该为0，表示从机给与应答
    SW_I2C_SCL = 0;
    Delay6us();
    //地址位发送完成
    return AckBit;
}

/**
  * @brief  IIC通信接收一个字节，并发送NACK（不应答）
  * @param  无
  * @retval 接收到的字节
  */
uint8_t SW_I2C_ReceiveByte()
{
    uint8_t i = 0;
    uint8_t Dat = 0x00;
    //开始读取：此时sda的控制权在从机
    SW_I2C_SDA = 1;
    Delay2ms();
    for (i = 0; i < 8; i++)
    {
        SW_I2C_SCL = 1;
        Delay6us();
        if (SW_I2C_SDA)
            Dat |= (0x80 >> i);
        SW_I2C_SCL = 0;
        Delay6us();
    }
    //。。。读取8次之后，发送NACK：
    SW_I2C_SDA = 1;
    Delay6us();
    SW_I2C_SCL = 1;
    Delay6us();
    SW_I2C_SCL = 0;
    Delay6us();
    return Dat;
}

#endif