#ifndef __AT24C02_H__
#define __AT24C02_H__

#include "SW_I2C.h"

uint8_t at24c02_address = 0x50;

/**
  * @brief  AC24C02从指定EEPROM地址读取一个字节
  * @param  ByteAddress 要读取的EEPROM地址 (0~255)
  * @retval 读取到的字节数据
  */
uint8_t AT24C02_Read_byte(uint8_t ByteAddress)
{
    uint8_t Dat;
    SW_I2C_StartBit();
    SW_I2C_SendSlaveAddress_and_RW_then_getAckBit(at24c02_address, 0);
    SW_I2C_SendByte_then_getAckBit(ByteAddress);
    SW_I2C_StopBit();
    Delay160us();
    SW_I2C_StartBit();
    SW_I2C_SendSlaveAddress_and_RW_then_getAckBit(at24c02_address, 1);
    Delay2ms();
    //开始读取：此时sda的控制权在从机
    Dat = SW_I2C_ReceiveByte();
    SW_I2C_StopBit();
    return Dat;
}


/**
  * @brief  AC24C02在指定EEPROM地址写入一个字节
  * @param  ByteAddress 要写入的EEPROM地址 (0~255)
  * @param  Dat 要写入的数据
  * @retval 无
  */
void AT24C02_Write_Byte(uint8_t ByteAddress, uint8_t Dat)
{
    SW_I2C_StartBit();
    SW_I2C_SendSlaveAddress_and_RW_then_getAckBit(at24c02_address, 0);
    SW_I2C_SendByte_then_getAckBit(ByteAddress);
    SW_I2C_SendByte_then_getAckBit(Dat);
    SW_I2C_StopBit();
    //写入完成数据之后，根据数据手册，必须等待5ms之后再发送下个数据
    Delay2ms();
    Delay2ms();
    Delay2ms();
}

/**
  * @brief  AC24C02从指定EEPROM地址写入多个
  * @param  ByteAddress 要写入的EEPROM地址 (0~255)
  * @param  length 数据的长度
  * @param  Datas 要写入的数据，可以是字符串或者字符数组
  * @retval 无
  */
void AT24C02_Write_Multi_Bytes(uint8_t ByteAddress,uint8_t length, const char *  Datas)
{
    uint8_t i;
    SW_I2C_StartBit();
    SW_I2C_SendSlaveAddress_and_RW_then_getAckBit(at24c02_address, 0);
    SW_I2C_SendByte_then_getAckBit(ByteAddress);
    for ( i = 0; i < length; i++)
    {
        SW_I2C_SendByte_then_getAckBit(Datas[i]);
    }
    SW_I2C_StopBit();
    //写入完成数据之后，根据数据手册，必须等待5ms之后再发送下个数据
    Delay2ms();
    Delay2ms();
    Delay2ms();
}



#endif