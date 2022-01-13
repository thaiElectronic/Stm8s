

#ifndef _UART_
#define _UART_


//#define SYSCLKS          16000000
#define UART_BAURATE    9600

extern char            vrsc_UART_ReceiveBuffer[64];
extern volatile unsigned char vruc_UART_Start, vruc_UART_Stop;
extern unsigned int    vrui_UART_CountReceive;


extern unsigned char RFID_UART_Num[7];
extern unsigned char vruc_UART_i;
//extern void Fn_UART_Init (void);

//extern char Fn_UART_GetChar (void);
extern void Fn_UART_GetChar (void);
extern void Fn_UART_SendChar (char _vruc_Data);
extern void Fn_UART_Pustf (char *_vruc_String);
extern void Fn_UART_PustNum(unsigned int _vrl_Number);


#endif