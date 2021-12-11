#ifndef __INDIVBTN_H__
#define __INDIVBTN_H__

#include "main.h"

/**
  * @brief  获取核心板上的三个按键状态
  * @param  无
  * @retval 0-4， ，1是最下面的，2，3是中间和上面， 0是没有按键
  */
uint8_t Get_onboard_key_num(void)
{
   uint8_t key_num = 0;
    if (P60 == 0){ DelayXms_AT44983(20);while (P60 == 0) ;DelayXms_AT44983(20);key_num = 1; }
    if (P61 == 0){ DelayXms_AT44983(20);while (P61 == 0) ;DelayXms_AT44983(20);key_num = 2; }
    if (P62 == 0){ DelayXms_AT44983(20);while (P62 == 0) ;DelayXms_AT44983(20);key_num = 3; }
   
   return key_num;
}

#endif