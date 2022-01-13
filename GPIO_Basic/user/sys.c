#include "sys.h"

void Fn_STM8_IWDTInit (void){
    IWDG->KR = 0x55;
    IWDG->PR = 7;
    IWDG->RLR = 0xFF;
    IWDG->KR = 0xcc;
    IWDG->KR = 0xAA;
}
void Fn_STM8_IWDRReLoad (void){
    IWDG->KR = 0xAA;
}

  void Sys_init()
  {
    Gpio_init();
    UART_Init(9600);
    Fn_Delayms(100);
    Gpio_ControlRelay(1);
    Fn_STM8_IWDTInit();
  }
  void Sys_Run()
  {
    char *data;
     if(UART_Flag())
    {
      if(UART_Compare(ADDRESS)==1)
      {
        json_t mem[300];
        json_t const* json = json_create( RRX, mem, sizeof mem / sizeof *mem );
        data = json_ReturnData(json,ADDRESS);
        if(strstr(data,"ON"))
        {
          Gpio_ControlRelay(0);
        }
        else if(strstr(data,"OFF"))
        {
           Gpio_ControlRelay(1);
        }
        //UART_Send_String(data);
        //UART_Send_String("\n");
      }
      else if(UART_Compare("OFF_ALL")==1)
      {
        Gpio_ControlRelay(1);
      }
    }
    Fn_STM8_IWDRReLoad();
  }