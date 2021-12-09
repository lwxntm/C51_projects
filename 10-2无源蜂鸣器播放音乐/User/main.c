#include "main.h"
#include "Timer0.h"

//播放小星星，可以修改define来播放其他音乐
#define music_table music_table_kiss_the_rain

#define SPEED 800


//音符与索引的关系
#define XZ0 0
#define L1  1
#define L1U  2
#define L2  3
#define L2U  4
#define L3  5
#define L4  6
#define L4U  7
#define L5  8
#define L5U  9
#define L6  10
#define L6U  11
#define L7  12

#define M1  13
#define M1U  14
#define M2  15
#define M2U 16
#define M3  17
#define M4  18
#define M4U  19
#define M5  20
#define M5U  21
#define M6  22
#define M6U  23
#define M7  24

#define H1  25
#define H1U  26
#define H2  27
#define H2U  28
#define H3  29
#define H4  30
#define H4U  31
#define H5  32
#define H5U 33
#define H6  34
#define H6U  35
#define H7  36

#define HH1  37
#define HH1U  38
#define HH2  39
#define HH2U  40
#define HH3  41
#define HH4  42
#define HH4U  43
#define HH5  44
#define HH5U 45
#define HH6  46
#define HH6U  47
#define HH7  48




sbit Buzzer = P4 ^ 2;

uint16_t code freq_table[] = {
    0, //休止符
    63625,
    63732,
    63833,
    63929,
    64019,
    64104,
    64185,
    64260,
    64332,
    64400,
    64463,
    64524,
    64580,
    64634,
    64685,
    64732,
    64778,
    64820,
    64860,
    64898,
    64934,
    64968,
    65000,
    65030,
    65058,
    65085,
    65110,
    65134,
    65157,
    65178,
    65198,
    65217,
    65235,
    65252,
    65268,
    65283,
    //下面是高高
    65297,
65311,
65323,
65335,
65346,
65357,
65367,
65377,
65386,
65394,
65402,
65409
};
uint8_t freq_select = 0;


// 未完成
uint8_t code music_table_kiss_the_rain[] = {
  0,4,
  0,4,
  0,4,
  0,1,
  M5,1,
  H1,1,
  H2,1,

  H2,2,
  H3,2,
  H3,8,
  XZ0,1,
  H1,1,
  H2,1,
  H3,1,

  H2,2,
  H5,2,
  H5,8,
  XZ0,1,
  H5,1,
  H6,1,
  H7,1,

  H7,2,
  HH1,2,
  HH1,6,
  HH2,2,
  HH3,2,
  HH2,2,
  HH1,2,
  //第一行结束

  XZ0,4,
  XZ0,4,
  XZ0,4,
  XZ0,4,

  L1,2,
  L5,2,
  M1,2,
  M2,2,
  M3,2,
  XZ0,2,
  0,4,


  


  0xff
};

uint8_t code music_table_xiaoxingxing[] = {
    13, 4,
    13, 4,
    20, 4,
    20, 4,
    22, 4,
    22, 4,
    20, 8,
    18, 4,
    18, 4,
    17, 4,
    17, 4,
    15, 4,
    15, 4,
    13, 8,

    0xff // 终止标志
};

uint8_t music_table_select = 0;

void main()
{
  init_all_gpio_to_std8051_status();

  Timer0_Init();
  while (1)
  {
    if (music_table[music_table_select] == 0xff)
    {
      TR0 = 0;
      continue;
    }

    freq_select = music_table[music_table_select++];
    Delay_ms(SPEED/4 * music_table[music_table_select++]);
    TR0 = 0;
    Delay_ms(5);
    TR0 = 1;
  }
}

void Timer0_Rountine() interrupt 1
{
  if (freq_table[freq_select])
  {
    TL0 = freq_table[freq_select] % 256; //设置定时初始值
    TH0 = freq_table[freq_select] / 256; //设置定时初始值
    Buzzer = ~Buzzer;
  }
}
