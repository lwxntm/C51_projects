#ifndef __LCD1602_H__
#define __LCD1602_H__

#include "STC8A8K64D4.H"
#include <intrins.h>
#include "TYPEDEF.h"

sbit LCD_RS = P7 ^ 4;
sbit LCD_RW = P7 ^ 5;
sbit LCD_E = P7 ^ 6;
#define LCD_DataPort P0

void __LCD_Delay1ms() //@44.242MHz
{
    unsigned char i, j;

    _nop_();
    i = 58;
    j = 114;
    do
    {
        while (--j)
            ;
    } while (--i);
}

void LCD_Write_Command(uint8_t Command)
{
    LCD_E = 0;
    LCD_RS = 0;             //表示指令
    LCD_RW = 0;             //表示写
    LCD_DataPort = Command; //把指令放到并口数据线上
    __LCD_Delay1ms();
    LCD_E = 1;
    __LCD_Delay1ms();
    LCD_E = 0;
    __LCD_Delay1ms();
}

void LCD_Write_Data(uint8_t Dat)
{
    LCD_E = 0;
    LCD_RS = 1;         //表示数据
    LCD_RW = 0;         //表示写
    LCD_DataPort = Dat; //把指令放到并口数据线上
    __LCD_Delay1ms();
    LCD_E = 1;
    __LCD_Delay1ms();
    LCD_E = 0;
    __LCD_Delay1ms();
}

void LCD_Init()
{
    LCD_Write_Command(0x38); ////八位数据接口，两行显示，5*7点阵
    LCD_Write_Command(0x0C); ////显示开，光标关，闪烁关
    LCD_Write_Command(0x06); ////数据读写操作后，光标自动加一，画面不动
    LCD_Write_Command(0x01); //清屏
}

void LCD_showChar(uint8_t line, uint8_t column, uint8_t c)
{
    LCD_Write_Command(0x80 | (((line - 1) * 0x40) + column - 1));
    LCD_Write_Data(c);
}
void LCD_showString(uint8_t line, uint8_t column, uint8_t *s)
{
    uint8_t i = 0;
    LCD_Write_Command(0x80 | (((line - 1) * 0x40) + column - 1));
    while (1)
    {
        if (!s[i])
            return;
        LCD_Write_Data(s[i++]);
    }
}

uint16_t __LCD__POW(uint16_t X, uint8_t Y)
{
    uint16_t Result = 1;
    while (Y--)
        Result *= X;
    return Result;
}

void LCD_ShowInt(uint8_t line, uint8_t column, uint16_t in, uint8_t len)
{
    uint8_t i = 0;
    LCD_Write_Command(0x80 | (((line - 1) * 0x40) + column - 1));
    for (i = len; i > 0; i--)
    {
        LCD_Write_Data('0'+((in / __LCD__POW(10, i - 1)) % 10));
    }
}

#endif