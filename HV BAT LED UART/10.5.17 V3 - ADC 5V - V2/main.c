#include "USER/SYSTEM.h"

unsigned int VR_num, sum_vr1, sum_tb;
char    *TempChar;
char RX_FLAG_END_LINE = 0;
char RRX[90];
void main(void){
    CLK_Config();
    GPIO_Config();
    TIM4_Config();
 //   Fn_UART_Init();
    UART1_Config();
    enableInterrupts();

    while (1){
        /*
        for(vruc_j=0; vruc_j<10;vruc_j++){
            VR_num = (unsigned int)(get_VR1());
            sum_vr1 = sum_vr1 + VR_num;
            Fn_DELAY_Long(10);
        }
        sum_tb = sum_vr1/10;
        sum_vr1 = 0;
        */
        if(RX_FLAG_END_LINE){
            RX_FLAG_END_LINE = 0;
            if(strstr(RRX, "HVBATT:")){
                TempChar  = strstr(RRX, "HVBATT:");
                //TempChar += 6;
                sum_tb = (TempChar[7] - '0')*10 + (TempChar[8] - '0');
                Fn_UART_PustNum(sum_tb);
            }        
//            Fn_UART_Pustf("da nhan duoc choi");
        }
        Fn_SYS_NumberLED(sum_tb);  
        
 //       Fn_SYS_NumberLED(sum_tb);    
        Fn_DELAY_Long(100);
    }
}



