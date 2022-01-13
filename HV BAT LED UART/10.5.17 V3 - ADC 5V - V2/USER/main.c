
#include "SYSTEM.h"

unsigned char   vruc_ALARM_Flag;
unsigned char   vruc_RightCard_Flag;
unsigned char   aruc_SYS_RFID_Var[56];
unsigned char   vruc_readEprom_i;
unsigned char   vruc_DisplayUART_i;

unsigned int    vrui_ALarm_i;
unsigned int    vrui_Over5s_i;
unsigned int    vrui_Time_i;

int main( void )
{
    unsigned int vruc_count=2500;
    unsigned char vruc_RFID_Change=0;
    Fn_SYS_InitCLKIO();
    GPIOD->DDR &= ~(1<<2);          //Mode Setup
    LOCK = 0;
    
    SPEAKER=0;
    
    Fn_UART_Init();
    
    Fn_UART_SendChar(13);           // new line /n
    Fn_UART_SendChar(10);           // new line /n 
    Fn_UART_Pustf ("---START MOONKEY---\n");
    
//    Fn_FLASH_Config();           
     
    while(1)
    {
    }
}	




