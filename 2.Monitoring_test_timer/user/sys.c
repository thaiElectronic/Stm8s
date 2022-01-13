#include "sys.h"

int vri_i;
unsigned int vrui_MC38 = 0;
unsigned int vrui_Phao = 0;
unsigned int vrui_NTC = 0;
//unsigned int vrui_MQ2 = 0;

void Sys_Init(void){
  InitialiseSystemClock();
  UART_Init(9600);
  TIM2_Init();
  //GPIOSENSOR_Init();
  //GPIO_Init(GPIOB, GPIO_PIN_7, GPIO_MODE_OUT_PP_LOW_FAST);
  //MCP3208_Init();
  enableInterrupts();
}

void Sensor_Read(void){
  unsigned int vrui_MQ2 = 0;
  vrui_MC38 = GPIO_ReadInputPin(PORT_MC38,PIN_MC38);
  if(vrui_MC38 > 0) vrui_MC38 = 1;
  
  vrui_Phao = GPIO_ReadInputPin(PORT_PHAO,PIN_PHAO);
  if(vrui_Phao > 0) vrui_Phao = 1;
  
  vrui_MQ2 = MCP3208_AnalogRead(0);	
  vrui_MQ2 = Map(vrui_MQ2,0,4095,0,5000);
  
  UART_Send_String("Value MQ2: ");
  UART_Send_Number(vrui_MQ2);
  UART_Send_String("(mv)\n");
  
  vrui_NTC = MCP3208_AnalogRead(CHANNEL_NTC);
  vrui_NTC = Map(vrui_NTC,0,4095,0,5000);
   
}
/*
void Sensor_disp(void){
  
  UART_Send_String("Value MC38: ");;
  UART_Send_Number(vrui_MC38);
  UART_Send_String("\n");
  
  UART_Send_String("Value PHAO: ");;
  UART_Send_Number(vrui_Phao);
  UART_Send_String("\n");
  
  UART_Send_String("Value MQ2: ");
  UART_Send_Number(vrui_MQ2);
  UART_Send_String("(mv)\n");
  
  UART_Send_String("Value NTC: ");
  UART_Send_Number(vrui_NTC);
  UART_Send_String("(mV)\n\n");
  
  vrui_MQ2 = 0;
  vrui_NTC = 0;
}


void Sys_process(void){
    if(vruc_stt == 1){
      Sensor_Read();
      vruc_stt = 0;
    }
  //  Sensor_disp();
}
*/
