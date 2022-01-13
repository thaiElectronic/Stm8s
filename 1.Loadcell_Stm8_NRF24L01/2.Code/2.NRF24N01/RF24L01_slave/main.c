#include "rf24l01.h"
#include "uart.h"
/*
RF24L01 stm8s demo
MASTER
This code receives two 32 bit ints from a master, and sends the result of the basic
mathematic operations involving them.

This is a proof of concept and not a copy and use library.
Adapt this code to your application.

Erwan Martin
Fall 2013
ARENIB Delta
http://delta.arenib.org/

License: MIT

RF24L01 connector pinout:
GND    VCC
CE     CSN
SCK    MOSI
MISO   IRQ

Connections:
  PC3 -> CE
  PC4 -> CSN
  PC7 -> MISO
  PC6 -> MOSI
  PC5 -> SCK

*/

uint8_t mutex;

int main( void ) {
  UART_Init(9600);
  RF24L01_init();
  UART_Send_String("xin chao");
  uint8_t rx_addr[5] = {0x04, 0xAD, 0x45, 0x98, 0x51};
  uint8_t tx_addr[5] = {0x44, 0x88, 0xBA, 0xBE, 0x42};
  RF24L01_setup(tx_addr, rx_addr, 12);

  //IRQ
  GPIO_Init(
    GPIOC,
    GPIO_PIN_4,
    GPIO_MODE_IN_FL_IT
  );
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOC, EXTI_SENSITIVITY_FALL_ONLY);
  enableInterrupts();

  while (1) {
      mutex = 0;
      RF24L01_set_mode_RX();
      while(!mutex);
      if (mutex == 1) {
        uint8_t recv_data[32];
        RF24L01_read_payload(recv_data, 32);
        UART_Send_String(recv_data);
        asm("nop"); //Place a breakpoint here to see memory
      }
  }

}

INTERRUPT_HANDLER(EXTI_PORTC_IRQHandler, 5) {
  uint8_t sent_info;
  if (sent_info = RF24L01_was_data_sent()) {
    //Packet was sent or max retries reached
    mutex = sent_info;
    RF24L01_clear_interrupts();
    return;
  }

  if(RF24L01_is_data_available()) {
    //Packet was received
    mutex = 1;
    RF24L01_clear_interrupts();
    return;
  }
  
  RF24L01_clear_interrupts();
}
