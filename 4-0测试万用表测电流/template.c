#include "STC8A8K64D4.h"

#include "alib.h"

#include <stdio.h>


void main()
{
  init_all_gpio_to_std8051_status();

  P35=1;
  //3V3到P35是3.13V
  //265R的电阻分压1.24V
  //红色led分压1.87V
}
