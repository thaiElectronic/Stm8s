#include "mcp3208.h"

void MCP3208_Init(void){
   SPI_DeInit();
   SPI_Init(SPI_FIRSTBIT_MSB, SPI_BAUDRATEPRESCALER_2, SPI_MODE_MASTER, SPI_CLOCKPOLARITY_HIGH, SPI_CLOCKPHASE_2EDGE,SPI_DATADIRECTION_2LINES_FULLDUPLEX, SPI_NSS_SOFT,0x00);
   SPI_Cmd(ENABLE);
   GPIO_Init(PORT_CS0_MCP3208,PIN_CS0_MCP3208, GPIO_MODE_OUT_PP_LOW_SLOW);
   GPIO_Init(PORT_CS1_MCP3208,PIN_CS1_MCP3208, GPIO_MODE_OUT_PP_LOW_SLOW);
}

unsigned char MCP3208x0_Transfer(unsigned char data){
  while(SPI_GetFlagStatus(SPI_FLAG_TXE)==RESET);
  SPI_SendData(data);
  while(SPI_GetFlagStatus(SPI_FLAG_RXNE)==RESET);
  return SPI_ReceiveData();
}

unsigned char MCP3208x1_Transfer(unsigned char data){
  while(SPI_GetFlagStatus(SPI_FLAG_TXE)==RESET);
  SPI_SendData(data);
  while(SPI_GetFlagStatus(SPI_FLAG_RXNE)==RESET);
  return SPI_ReceiveData();
}

unsigned int MCP3208x0_AnalogRead(unsigned char vruc_channel0){
  unsigned int vrus_ouputdata0;
  unsigned char vruc_msb0 = 0, vruc_lsb0 = 0;
  unsigned char channelBits0 = vruc_channel0<<6;
  MCP3208_CS0_LOW;
  MCP3208_CS1_HIGH;
  if(vruc_channel0>3)
    MCP3208x0_Transfer(0x07); 
  else
    MCP3208x0_Transfer(0x06);
  vruc_msb0 = MCP3208x0_Transfer(channelBits0);
  vruc_lsb0 = MCP3208x0_Transfer(0x00);
  MCP3208_CS0_HIGH;
  vruc_msb0 = vruc_msb0 & 0x0f;
  vrus_ouputdata0 = vruc_msb0<<8 | vruc_lsb0; 
  return vrus_ouputdata0;
}

unsigned int MCP3208x1_AnalogRead(unsigned char vruc_channel1){
  unsigned int vrus_ouputdata1;
  unsigned char vruc_msb1 = 0, vruc_lsb1 = 0;
  unsigned char channelBits1 = vruc_channel1<<6;
  MCP3208_CS1_LOW;
  MCP3208_CS0_HIGH;
  if(vruc_channel1>3)
    MCP3208x1_Transfer(0x07); 
  else
    MCP3208x1_Transfer(0x06);
  vruc_msb1 = MCP3208x1_Transfer(channelBits1);
  vruc_lsb1 = MCP3208x1_Transfer(0x00);
  MCP3208_CS1_HIGH;
  MCP3208_CS0_LOW;
  vruc_msb1 = vruc_msb1 & 0x0f;
  vrus_ouputdata1 = vruc_msb1<<8 | vruc_lsb1; 
  return vrus_ouputdata1;
}
 unsigned char i = 0,j = 0;
void MCP3208_Test(void){
 
  for(i = 0; i < 8; i++){
    UART_Send_String("ADCx0 -- ");
    UART_Send_Number(i);
    UART_Send_String(": ");
    UART_Send_Number(MCP3208x0_AnalogRead(i));
    UART_Send_String("\n");
    Fn_Delayms(5);
  }
  for(j = 0; j< 8; j++){
    UART_Send_String("ADCx1 -- ");
    UART_Send_Number(j);
    UART_Send_String(": ");
    UART_Send_Number(MCP3208x1_AnalogRead(j));
    UART_Send_String("\n");
    Fn_Delayms(5);
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

