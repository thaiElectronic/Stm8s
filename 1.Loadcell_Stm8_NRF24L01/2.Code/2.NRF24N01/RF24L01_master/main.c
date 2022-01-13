#include "rf24l01.h"
#include "uart.h"
/*
RF24L01 stm8s demo
MASTER
This code sends two 32 bit ints to a slave, and gets the result of the basic
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


int main( void )
{
  RF24L01_init();
  uint8_t tx_addr[5] = {0x04, 0xAD, 0x45, 0x98, 0x51};
  uint8_t rx_addr[5] = {0x44, 0x88, 0xBA, 0xBE, 0x42};
  RF24L01_setup(tx_addr, rx_addr, 12);
  RF24L01_set_mode_TX();
  
  while(1) {
      uint8_t buffer_to_send[] = "Quang Bien - Nhan_ma25";
      RF24L01_write_payload(buffer_to_send, sizeof(buffer_to_send)+1);
      while(!RF24L01_was_data_sent());
      Fn_Delayms(500);
  }

}
