#include "sys.h"

void Gpio_init(void)
{
//  GPIOD->DDR &= ~(1 << 4);
//  GPIOD->CR1 |= (1 << 4);
//  GPIOD->CR2 |= (1 << 4);
  Gpio_ControlRelay(1);
  GPIO_Init(GPIOD, GPIO_PIN_4, GPIO_MODE_OUT_PP_HIGH_SLOW);
}

void Gpio_ControlRelay(unsigned char mode)
{
    if(mode)
    {
      GPIO_WriteHigh(GPIOD,GPIO_PIN_4);
    }
    else
    {
      GPIO_WriteLow(GPIOD,GPIO_PIN_4);
    }
}