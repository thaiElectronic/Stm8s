#include "mcp3208.h"

void MCP3208_Init(void){
   SPI_DeInit();
   SPI_Init(SPI_FIRSTBIT_MSB, SPI_BAUDRATEPRESCALER_2, SPI_MODE_MASTER, SPI_CLOCKPOLARITY_HIGH, SPI_CLOCKPHASE_2EDGE,SPI_DATADIRECTION_2LINES_FULLDUPLEX, SPI_NSS_SOFT,0x00);
   SPI_Cmd(ENABLE);
   GPIO_Init(GPIOE,GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_SLOW);
}

unsigned char MCP3208_Transfer(unsigned char data){
  while(SPI_GetFlagStatus(SPI_FLAG_TXE)==RESET);
  SPI_SendData(data);
  while(SPI_GetFlagStatus(SPI_FLAG_RXNE)==RESET);
  return SPI_ReceiveData();
}

unsigned int MCP3208_AnalogRead(unsigned char vruc_channel){
  unsigned int vrus_ouputdata;
  unsigned char vruc_msb = 0, vruc_lsb = 0;
  unsigned char channelBits = vruc_channel<<6;
  MCP3208_CSLow;
  if(vruc_channel>3)
    MCP3208_Transfer(0x07); 
  else
    MCP3208_Transfer(0x06);
  vruc_msb = MCP3208_Transfer(channelBits);
  vruc_lsb = MCP3208_Transfer(0x00);
  MCP3208_CSHigh;
  vruc_msb = vruc_msb & 0x0f;
  vrus_ouputdata = vruc_msb<<8 | vruc_lsb; 
  return vrus_ouputdata;

void MCP3208_Test(void){
  unsigned char i = 0;
  for(i=0; i<1; i++){
    UART_Send_String("ADC ");
    UART_Send_Number(i);
    UART_Send_String(": ");
    UART_Send_Number(MCP3208_AnalogRead(i));
    UART_Send_String("\n");
  }
  UART_Send_String("\n-----------------------\n");
}

int Map(int x, int in_min, int in_max, int out_min, int out_max){
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
/*
float Map(float x, float in_min, float in_max, float out_min, float out_max){
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
*/

