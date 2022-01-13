#include "i2c.h"
#include "stm8s_i2c.h"
void I2C_Start(unsigned char Mode);
void I2C_Stop(void);
void I2C_Write_Data(uint8_t Data);
void I2C_Write_add(uint8_t data, uint8_t mode);
uint8_t I2C_Read_NAK(void);
uint8_t I2C_Read_ACK(void);
#define MPU_TIME_OUT 1600
#define ERROR -1;
static uint16_t time_out = 0;

void ssd1306_I2C_Init()
{
   //I2C_Init(100000, 0x3c, I2C_DUTYCYCLE_2, I2C_ACK_CURR, I2C_ADDMODE_7BIT, 16); 
  
  I2C->CR1 = 0;
  I2C->FREQR = 16;
  I2C->CCRL = 78;
  I2C->CCRH &= 0x00;
  I2C->OARH = 0x40;
  I2C->TRISER = 17;
  I2C->CR1 = I2C_CR1_PE;
  
}

char I2CdataTX(unsigned char address, unsigned char *txbuf, int txnum)
{
  int i;
  I2C_Start(0);
  I2C_Write_add(address,0);
  for(i = 0 ; (i < txnum) ; i++)
  {
       I2C_Write_Data(txbuf[i]);
  }
  I2C_Stop();
}


void ssd1306_I2C_Write( uint8_t address, uint8_t reg, uint8_t data)
{
  I2C_Start(0);
  I2C_Write_add(address,0);
  I2C_Write_Data(reg);
  I2C_Write_Data(data);
  I2C_Stop();
}

void ssd1306_I2C_WriteMulti(uint8_t address, uint8_t reg, uint8_t *data, uint16_t count)
{
  uint8_t i;
  I2C_Start(0);
  I2C_Write_add(address,0);
  for (i = 0; i < count; i++)
  {
    I2C_Write_Data(data[i]);
  }
   I2C_Stop();
}

void I2C_Start(unsigned char Mode)
{
  I2C->CR2 |= I2C_CR2_START;//|(0<<I2C_CR2_STOP);
  time_out=0;
  while (!(I2C->SR1 & I2C_SR1_SB))
  {
    time_out++;
    if (time_out == MPU_TIME_OUT)
      break;
  }
  if(Mode)
    I2C->CR2 |= I2C_CR2_ACK;
}

void I2C_Stop(void)
{
  
  I2C->CR2 |= I2C_CR2_STOP;
}

void I2C_Write_Data(uint8_t data)
{
  volatile int reg;
  reg = I2C->SR1;
  reg = I2C->SR3;
  I2C->DR = data;
  time_out=0;
  while (!(I2C->SR1 & I2C_SR1_TXE))
  {
    time_out++;
    if (time_out == MPU_TIME_OUT)
      break;
  }  
}

void I2C_Write_add(uint8_t add, uint8_t mode)
{
  volatile int reg;
  reg = I2C->SR1;
  reg = I2C->SR3;
  time_out=0;
  I2C->DR = (add<<1) | mode;
  if (mode == 1) {
    I2C->OARL = 0; 
    I2C->OARH = 0;
  }
  while (!(I2C->SR1 & I2C_SR1_ADDR))
  {
    time_out++;
    if (time_out == MPU_TIME_OUT)
      break;
  }
  I2C->SR1 &= ~I2C_SR1_ADDR;
}

uint8_t I2C_Read_NAK(void)
{
  volatile uint8_t reg;
  reg = I2C->SR1;
  reg = I2C->SR3;
  time_out=0;
  I2C->CR2 &= ~I2C_CR2_ACK;
  I2C_Stop();
  while (!(I2C->SR1 & (I2C_SR1_RXNE)))
  {
    time_out++;
    if (time_out == MPU_TIME_OUT)
      break;
  }
  return I2C->DR;

}

uint8_t I2C_Read_ACK(void)
{
  volatile uint8_t reg;
  reg = I2C->SR1;
  reg = I2C->SR3;
  I2C->CR2 |= I2C_CR2_ACK;
  time_out=0;
  while (!(I2C->SR1 & I2C_SR1_RXNE))
  {
    time_out++;
    if (time_out == MPU_TIME_OUT)
      break;
  }
  return I2C->DR;
}
