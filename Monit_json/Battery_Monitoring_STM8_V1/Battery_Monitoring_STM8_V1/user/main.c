#include "sys.h"
#include <stdio.h>
#include <stdlib.h>
#include "json-maker.h"

extern char vruc_Stt;

struct data {
    char const* Name;
    int         ID;
};

/* Add a data object property in a JSON string. */
char* json_data( char* dest, char const* name, struct data const* data ) { 
    dest = json_objOpen( dest, NULL );
    dest = json_str( dest, "Name",  data->Name );
    dest = json_int( dest, "ID", data->ID );
    dest = json_objClose( dest );
    return dest;
}

/*
  * Convert a data structure to a root JSON object.
  * @param dest Destination memory block.
  * @param data Source data structure.
  * @return  The JSON string length. 
*/
int data_to_json( char* dest, struct data const* data ) {
    char* p = json_data( dest, NULL, data );
    p = json_end( p );
    return p - dest;
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
  int value;
  InitialiseSystemClock();
  UART_Init(115200);
  GPIO_Config();
  MCP3208_Init();
  enableInterrupts();
  while (1){
//  MCP3208_Test();
    value = MCP3208_AnalogRead(0);
//  UART_Send_Number(value);
//  UART_Send_String("\n");
    
    struct data const data = {
      .Name     = "Name",
      .ID	= value,     
    };
    
    char buff[512];
    
    int len = data_to_json( buff, &data );
    
    UART_Send_String( buff);
    UART_Send_String("\n");
    
    Fn_Delayms(1000);
  }
}

/*
int main(){
  GPIOE_Config();
  while(1){
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