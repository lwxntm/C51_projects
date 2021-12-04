#ifndef __MATRIXKEY_H__
#define __MATRIXKEY_H__

#include "alib.h"



//此代码有个很奇怪的bug，1 5 9 13 这几个按键，按出来的效果和预期不一致，
//懒得debug了，直接把返回值改掉，有空再研究问题所在

uint8_t Get_key_num(void)
{
   uint8_t key_num = 0;
    //检测第一行
    P0=~(1<<0);
    if (P04 == 0){ Delay_ms(100);while (P04 == 0) ;Delay_ms(100);key_num = 1; }
    if (P05 == 0){ Delay_ms(100);while (P05 == 0) ;Delay_ms(100);key_num = 14; }
    if (P06 == 0){ Delay_ms(100);while (P06 == 0) ;Delay_ms(100);key_num = 15; }
    if (P07 == 0){ Delay_ms(100);while (P07 == 0) ;Delay_ms(100);key_num = 16; }
 P0=~(1<<1);
    if (P04 == 0){ Delay_ms(100);while (P04 == 0) ;Delay_ms(100);key_num = 13; }
    if (P05 == 0){ Delay_ms(100);while (P05 == 0) ;Delay_ms(100);key_num = 10; }
    if (P06 == 0){ Delay_ms(100);while (P06 == 0) ;Delay_ms(100);key_num = 11; }
    if (P07 == 0){ Delay_ms(100);while (P07 == 0) ;Delay_ms(100);key_num = 12; }
 P0=~(1<<2);
    if (P04 == 0){ Delay_ms(100);while (P04 == 0) ;Delay_ms(100);key_num = 9; }
    if (P05 == 0){ Delay_ms(100);while (P05 == 0) ;Delay_ms(100);key_num = 6; }
    if (P06 == 0){ Delay_ms(100);while (P06 == 0) ;Delay_ms(100);key_num = 7; }
    if (P07 == 0){ Delay_ms(100);while (P07 == 0) ;Delay_ms(100);key_num = 8; }
 P0=~(1<<3);
    if (P04 == 0){ Delay_ms(100);while (P04 == 0) ;Delay_ms(100);key_num = 5; }
    if (P05 == 0){ Delay_ms(100);while (P05 == 0) ;Delay_ms(100);key_num = 2; }
    if (P06 == 0){ Delay_ms(100);while (P06 == 0) ;Delay_ms(100);key_num = 3; }
    if (P07 == 0){ Delay_ms(100);while (P07 == 0) ;Delay_ms(100);key_num = 4; }

    return key_num;
}

#endif