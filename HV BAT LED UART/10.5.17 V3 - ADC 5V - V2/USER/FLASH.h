#ifndef __Flash_H_
#define __Flash_H_

#include "stm8s.h"


#define FLASH_RASS_KEY1 ((uint8_t)0x56) /*!< First RASS key */
#define FLASH_RASS_KEY2 ((uint8_t)0xAE) /*!< Second RASS key */
#define FLASH_CLEAR_BYTE ((uint8_t)0x00)

typedef enum {
    FLASH_PROGRAMTIME_STANDARD = (uint8_t)0x00, /*!< Standard programming time fixed at 1/2 tprog */
    FLASH_PROGRAMTIME_TPROG    = (uint8_t)0x01  /*!< Programming time fixed at tprog */
} FLASH_ProgramTime_TypeDef;
typedef enum {
    FLASH_MEMTYPE_PROG      = (uint8_t)0xFD, /*!< Program memory */
    FLASH_MEMTYPE_DATA      = (uint8_t)0xF7  /*!< Data EEPROM memory */
} FLASH_MemType_TypeDef;
typedef enum {
    FLASH_FLAG_DUL       = (uint8_t)0x08,     /*!< Data EEPROM unlocked flag */
    FLASH_FLAG_EOP       = (uint8_t)0x04,     /*!< End of programming (write or erase operation) flag */
    FLASH_FLAG_PUL       = (uint8_t)0x02,     /*!< Flash Program memory unlocked flag */
    FLASH_FLAG_WR_PG_DIS = (uint8_t)0x01      /*!< Write attempted to protected page flag */
} FLASH_Flag_TypeDef;


void Fn_FLASH_DeInit(void);
void Fn_FLASH_SetProgrammingTime(FLASH_ProgramTime_TypeDef FLASH_ProgTime);
void Fn_FLASH_Unlock(FLASH_MemType_TypeDef FLASH_MemType);
void Fn_FLASH_Lock(FLASH_MemType_TypeDef FLASH_MemType);
FlagStatus Fn_FLASH_GetFlagStatus(FLASH_Flag_TypeDef FLASH_FLAG);
void Fn_FLASH_ProgramByte(uint32_t Address, uint8_t Data);
uint8_t Fn_FLASH_ReadByte(uint32_t Address);
void Fn_FLASH_EraseByte(uint32_t Address);
void Fn_FLASH_Config(void);

#endif