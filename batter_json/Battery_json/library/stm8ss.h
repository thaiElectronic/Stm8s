#ifndef STM8SS_H
#define STM8SS_H

#include <stdint.h>

#define _MEM_(mem_addr)         (*(volatile uint8_t *)(mem_addr))
#define _SFR_(mem_addr)         (*(volatile uint8_t *)(0x5000 + (mem_addr)))


#endif /* STM8S_H */
