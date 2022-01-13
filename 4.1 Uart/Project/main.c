#include "stm8s.h"
#include "uart.h"

void delay_ms(unsigned int time){
  int i,j;
  for(j = 0; j < time; j++){
    for(i = 0; i < 400; i++){};
  }
}

int main( void ){
  UART_Init(9600);
  while(1){
    UART_Send_String("Welcome to channel Thai MCU\n");
    delay_ms(500);
  }
}
