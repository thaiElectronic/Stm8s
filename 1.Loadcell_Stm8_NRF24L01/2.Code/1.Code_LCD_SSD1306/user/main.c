
#include "stm8s.h"
#include "uart.h"
#include "DELAY.h"
#include "i2c.h"
#include "ssd1306.h"
#include "stm8s_gpio.h"


int main()
{
  UART_Init(9600);
  const unsigned char Sine[] = {0, 11, 22, 33, 43, 53, 62, 71, 78, 85, 90, 94, 97, 99, 100};
  unsigned char code = 0x20;
  int i = 0, j = 0, dw = 0;
  CLK->CKDIVR = 0;
  CLK->PCKENR1 = 0xff;
  CLK->PCKENR2 = 0xff;
  Fn_Delayms(10);
  ssd1306_I2C_Init();
  Fn_Delayms(10);
  initOLED();
  Fn_Delayms(10);
  displayON(1);
  Fn_Delayms(10);
  SetYX(1, 2);
  WriteString("1", NORMAL);
  Fn_Delayms(2000);
  
  while (1)
  {
  
    clearOLED(NORMAL);
    for (int i = 0 ; i < 8 ; i++)
    {
      SetYX(i, 0);
      for (int j = 0 ; j < 16 ; j++)
      {
        WriteCharacter(code++, NORMAL);
        if (code > 0x7F)
          code = 0x20;
      }
    }
    Fn_Delayms(1000);
  }
}