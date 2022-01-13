#include <string.h>
#include <ctype.h>
#include "stm8s.h"
#include "uart.h"
#include "json-maker.h"
#include "tiny-json.h"
#include "DELAY.H"
#include "mcp3208.h"
#include "stm8s_gpio.h"
#include "stdio.h"
#include "stdlib.h"

void delay_ms(int a){
  for (int i = 0; i < a; i++)
    for (int index = 0; index < 400; index++);
}
struct data {
    int MQ2_Value;
    int NTC_Value;
};
int datajson( char* dest, struct data const* src ) {
    char* p = dest;                       
    p = json_objOpen( p, NULL );         
    p = json_int( p, "MQ2_Value", src->MQ2_Value );
    p = json_int( p, "NTC_Value", src->NTC_Value );   
    p = json_objClose( p );             
    p = json_end( p );                
    return p - dest;       
}

int MQ2_Value;
int main(){
  
//  InitialiseSystemClock();
//  UART_Init(115200);
  MCP3208_Init();
  
  MQ2_Value = MCP3208x0_AnalogRead(0);
 
  char buff[512];
   UART_Send_String((char * )datajson);
   UART_Send_String("\n");

  while(1){
  //  UART_Send_String(buff);
   // UART_Send_String("\n");
  }
}

/*
int main( void ){

  char CR[]   ="{\"Name\":\"thai\",\"Age\":\"21\",\"Address\":\"Thai Binh\"}";
  json_t mem[100];
  json_t const* json = json_create( CR, mem, sizeof mem / sizeof *mem );
  UART_Init(9600);
  while (1)
  {
  
    UART_Send_String(json_ReturnData(json,"Name"));
    UART_Send_String("\n");
    UART_Send_String(json_ReturnData(json,"Age"));
    UART_Send_String("\n");
    UART_Send_String(json_ReturnData(json,"Address"));
    UART_Send_String("\n");
//    UART_Send_String(json_ReturnData(json,"University"));
//    UART_Send_String("\n");
    Fn_Delayms(500);

    if(UART_Flag())
    {
      UART_Send_Array_RX();
    }
  }
}
*/