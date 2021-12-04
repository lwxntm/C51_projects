
#include "STC8A8K64D4.h"

#include "alib.h"
#include "LCD1602.h"
#include <stdio.h>
#include "MatrixKey.h"

uint8_t main_key_num = 0;
char input_ascii=0;

uint8_t num_line=0;  //当前数字在第一行还是第二行的flag
uint8_t operator =' ';


uint16_t line1_num=0;
uint16_t line2_num=0;
uint16_t result=0;
/*
做一个矩阵键盘计算器：
      789+
      456-
      123*
      0B=/

      其中的B是复位，懒得做退格键了。。反正就5位
*/

uint8_t convert_key_to_ascii(uint8_t key){
  switch (key)
  {
  case 1:return '7';
  case 2:return '8';
  case 3:return '9';
  case 4:return '+';
  case 5:return '4';
  case 6:return '5';
  case 7:return '6';
  case 8:return '-';
  case 9:return '1';
  case 10:return '2';
  case 11:return '3';
  case 12:return '*';
  case 13:return '0';
  case 14:return '\b';
  case 15:return '=';
  case 16:return '/';
  
  default:
    return 0;
  }
}

void calc_result(){
  switch (operator)
  {
  case '+':
    result=line1_num+line2_num;
    break;
  case '-':
    result=line1_num-line2_num;
    break;
  case '*':
    result=line1_num*line2_num;
    break;
  case '/':
    result=line1_num/line2_num;
    break;
  default:
    break;
  }
  LCD_ShowChar(2,7,'=');
  LCD_ShowNum(2,8,result,5);

}

void main()
{
  init_all_gpio_to_std8051_status();
  LCD_Init();
  Delay_ms(10);
  LCD_ShowNum(1,1,line1_num,5);
  LCD_ShowNum(2,1,line2_num,5);
  while (1)
  {
    main_key_num=Get_key_num() ;
    if (!main_key_num) 
      continue; //如果没有输入，重新获取
    
    switch (convert_key_to_ascii(main_key_num))
    {

    case '+':
      operator='+';
      num_line=1;
      break;
    case '-':
      operator='-';
      num_line=1;
      break;
    case '*':
      operator='*';
      num_line=1;
      break;
    case '/':
      operator='/';
      num_line=1;
      break;
    case '=':
      calc_result();
      break;
    case '\b':
      IAP_CONTR=1<<5; //根据数据手册，写ISP_CONTR的B5, SWRST寄存器 可以实现软件复位
      break;
    
    
    default:
    if (num_line==0)
    line1_num=line1_num*10 +(convert_key_to_ascii(main_key_num)-48); //(main_key_num-48) 是ascii数字转十进制数字的差距
    else
    line2_num=line2_num*10 +(convert_key_to_ascii(main_key_num)-48); 
      break;
    }

    LCD_ShowNum(1,1,line1_num,5);
    LCD_ShowNum(2,1,line2_num,5);
    LCD_ShowChar(1,8,operator);
      
  }
}
