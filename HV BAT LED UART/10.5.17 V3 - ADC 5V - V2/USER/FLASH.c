#include "Flash.h"

void Fn_FLASH_DeInit(void)
{
    FLASH->CR1 = FLASH_CR1_RESET_VALUE;
    FLASH->CR2 = FLASH_CR2_RESET_VALUE;
    FLASH->NCR2 = FLASH_NCR2_RESET_VALUE;
    FLASH->IAPSR &= (uint8_t)(~FLASH_IAPSR_DUL);
    FLASH->IAPSR &= (uint8_t)(~FLASH_IAPSR_PUL);
    (void) FLASH->IAPSR; /* Reading of this register causes the clearing of status flags */
}

void Fn_FLASH_SetProgrammingTime(FLASH_ProgramTime_TypeDef FLASH_ProgTime)
{
    FLASH->CR1 &= (uint8_t)(~FLASH_CR1_FIX);
    FLASH->CR1 |= (uint8_t)FLASH_ProgTime;
}

void Fn_FLASH_Unlock(FLASH_MemType_TypeDef FLASH_MemType)
{
    /* Unlock program memory */
    if (FLASH_MemType == FLASH_MEMTYPE_PROG)
    {
        FLASH->PUKR = FLASH_RASS_KEY1;
        FLASH->PUKR = FLASH_RASS_KEY2;
    }
    /* Unlock data memory */
    else
    {
        FLASH->DUKR = FLASH_RASS_KEY2; /* Warning: keys are reversed on data memory !!! */
        FLASH->DUKR = FLASH_RASS_KEY1;
    }
}

void Fn_FLASH_Lock(FLASH_MemType_TypeDef FLASH_MemType)
{
  /* Lock memory */
  FLASH->IAPSR &= (uint8_t)FLASH_MemType;
}

FlagStatus Fn_FLASH_GetFlagStatus(FLASH_Flag_TypeDef FLASH_FLAG)
{
    FlagStatus status = RESET;
    /* Check the status of the specified FLASH flag */
    if ((FLASH->IAPSR & (uint8_t)FLASH_FLAG) != (uint8_t)RESET)
    {
        status = SET; /* FLASH_FLAG is set */
    }
    else
    {
        status = RESET; /* FLASH_FLAG is reset*/
    }
    /* Return the FLASH_FLAG status */
    return status;
}

void Fn_FLASH_ProgramByte(uint32_t Address, uint8_t Data)
{
    *(PointerAttr uint8_t*) (uint16_t)Address = Data;
}

uint8_t Fn_FLASH_ReadByte(uint32_t Address)
{   
    /* Read byte */
    return(*(PointerAttr uint8_t *) (uint16_t)Address); 

}

void Fn_FLASH_EraseByte(uint32_t Address)
{
    /* Erase byte */
   *(PointerAttr uint8_t*) (uint16_t)Address = FLASH_CLEAR_BYTE; 

}
void Fn_FLASH_Config(void)
{
	Fn_FLASH_DeInit();
	/* Define flash programming Time*/
	Fn_FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_STANDARD);

//	  Fn_FLASH_Unlock(FLASH_MEMTYPE_PROG);
	/* Wait until Flash Program area unlocked flag is set*/
//	  while (Fn_FLASH_GetFlagStatus(FLASH_FLAG_PUL) == RESET){}
	/* Unlock flash data eeprom memory */
	Fn_FLASH_Unlock(FLASH_MEMTYPE_DATA);
	/* Wait until Data EEPROM area unlocked flag is set*/
	while (Fn_FLASH_GetFlagStatus(FLASH_FLAG_DUL) == RESET){}
}