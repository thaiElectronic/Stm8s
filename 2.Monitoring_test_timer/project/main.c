#include "sys.h"

unsigned char vruc_stt = 0;

int main( void ){ 
  
  Sys_Init();
  while (1){

//    MCP3208_Test();
//    Fn_Delayms(1000);
    Run_timer2();
  }     
}
