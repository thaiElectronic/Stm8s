#include "sys.h"
#include <stdio.h>
#include <stdlib.h>
#include "json-maker.h"

extern char vruc_Stt;
int i = 0;
int value;

#define CB1 "MQ5"
#define CB2 "NTC" 

char *Name_sensor[20]= {CB1, CB2,"CB3", "CB4", "CB5", "CB6", "CB7","CB8", "CB9", "CB10", "CB11", "CB12","CB13", "CB14", "CB15", "CB16"}; 


struct Data_Sensor{
	float Value_Sensor;
	char const* Name_Sensor;
	char array_flag;
};

char* json_data( char* dest, char const* name, struct Data_Sensor const* Data_SR ) { 
    dest = json_objOpen( dest, NULL );
    dest = json_str( dest, "Name",  Data_SR->Name_Sensor );
    dest = json_int( dest, "Value", Data_SR->Value_Sensor );
    dest = json_objClose( dest );

    return dest;
}

int data_to_json( char* dest, struct Data_Sensor const* Data_SR ) {
    char* p = json_data( dest, NULL, Data_SR );
    p = json_end( p );
    return p - dest;
}

void Dong_goi_json(char* Name, int Number){
  
  value = MCP3208_AnalogRead(Number);
  
  struct Data_Sensor const Data_SR = {
      .Name_Sensor     = Name,
        
    };
   char buff[512];
    
   int len = data_to_json( buff, &Data_SR );
    
   UART_Send_String( buff);
   UART_Send_String("\n");
}

void GPIO_Config(){
  GPIOB->ODR = 0;
  GPIOB->DDR = (1<<7);
  GPIOB->CR1 = (1<<7);
  GPIOB->CR2 = (1<<7);
}

void GPIOE_Config(){
  GPIOE->ODR = 0;
  GPIOE->DDR = 0xff;
  GPIOE->CR1 = 0xff;
  GPIOE->CR2 = 0xff;
}

int main( void ){

  InitialiseSystemClock();
  UART_Init(9600);
  GPIO_Config();
  MCP3208_Init();
  enableInterrupts();
  while (1){
//  MCP3208_Test();
 
//  UART_Send_Number(value);
//  UART_Send_String("\n");
    Dong_goi_json(Name_sensor[0],0);
    Dong_goi_json(Name_sensor[1],1);
    Fn_Delayms(1000);
  }
}

/*
int main(){
  GPIOE_Config();

    GPIOE->ODR = 0xff;
    
    Fn_Delayms(50);
    GPIOE->ODR = 0x00;
    Fn_Delayms(50);
  }
}
*/
/*
GPIOSENSOR_ReadInput(GPIO_ReadInputPin(GPIOA,GPIO_PIN_1), (SS_TypeInput*)(&vrts_ButtonA));
    GPIOSENSOR_ReadInput(GPIO_ReadInputPin(GPIOA,GPIO_PIN_4), (SS_TypeInput*)(&vrts_ButtonB));
    if(vrts_ButtonA.vruc_FlagChange)
    {
      vrts_ButtonA.vruc_FlagChange = 0;
      UART_Send_String("BT1");
    }
    
    if(vrts_ButtonB.vruc_FlagChange)
    {
      vrts_ButtonB.vruc_FlagChange = 0;
      UART_Send_String("BT2");
    }
   Fn_Delayms(1);
*/