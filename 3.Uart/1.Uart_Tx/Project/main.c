#include "stm8s.h"
#include "stm8s_uart1.h"

void usart1_init(){
  UART1_Init(9600,UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO, UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);
  UART1_Cmd(ENABLE);
}

int main(){
  usart1_init();
//  UART_Send_String("Salem\n");
  while(1){
    UART1_SendData8('T');
    Fn_Delayms(500);
  }
}
