#include "sys.h"

int main( void )
{
  Sys_init();
  while (1)
  {
   Sys_Run();
  }
}