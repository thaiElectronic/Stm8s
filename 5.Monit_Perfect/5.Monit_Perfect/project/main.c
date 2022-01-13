#include "sys.h"

//extern unsigned int Flag_Read;

unsigned int MC38_value= 0, PHAO_value = 0;

int main(){
  Sys_Init();
 // UART_Send_String("THAI MCU");
 // GPIO_Init(PORT_CS1_MCP3208,PIN_CS1_MCP3208, GPIO_MODE_OUT_PP_LOW_SLOW);
 //  GPIO_Init(PORT_CS0_MCP3208,PIN_CS0_MCP3208, GPIO_MODE_OUT_PP_LOW_SLOW);
  while(1){
    Output();

    /*
    if(Flag_Read == 1){
      Flag_Read = 0;/.klm,..,.
      Sensor_Disp();
    }
    Fn_Delayms(100);
    TIM4_Cmd(ENABLE);
    */
    
    /*
    MC38_value = GPIO_ReadInputPin(PORT_MC38,PIN_MC38);
    UART_Send_String("MC38: ");
    UART_Send_Number(MC38_value);
    UART_Send_String("\n");
    Fn_Delayms(100);

    GPIO_WriteHigh(GPIOE,GPIO_PIN_6);
    Fn_Delayms(500);
        GPIO_WriteLow(GPIOE,GPIO_PIN_6);
    Fn_Delayms(500);*/
  //  MCP3208_Test();Fn_Delayms(1000);
      
  }
}