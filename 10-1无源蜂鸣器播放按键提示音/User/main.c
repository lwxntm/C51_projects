#include "main.h"
#include "IndivBtn.h"
#include "Buzzer.h"

uint8_t key_num = 0;
uint16_t i = 0;
void main()
{
  init_all_gpio_to_std8051_status();
  while (1)
  {
    key_num = Get_onboard_key_num();
    if (key_num)
    {
      Buzzer_xms(100);
    }
  }
}
