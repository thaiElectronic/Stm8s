/**
  ********************************************************************************
  * @file    stm8s_uart1.h
  * @author  Nguyen Quang Bien
  * @version 
  * @date    
  * @brief   
  *******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __I2C_H
#define __I2C_H

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#define SSD1306_I2C_ADDR         0x78    

void ssd1306_I2C_Init();
void ssd1306_I2C_Write( uint8_t address, uint8_t reg, uint8_t data);
void ssd1306_I2C_WriteMulti(uint8_t address, uint8_t reg, uint8_t *data, uint16_t count);

#endif /* __STM8S_UART1_H */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/