#include "include/common/common.h"
#ifndef __PCB_H__
#define __PCB_H__
#define MAX_STACK 1024
struct ProgramControlBlock{
	uint8_t stack[MAX_STACK];
	uint8_t* ptr;
	uint8_t is_used;
	uint16_t dataseg;
	uint16_t codeseg;
};
typedef struct ProgramControlBlock pcb;
void init_pcb();
int new_pcb(uint16_t,uint16_t,uint32_t);
void start_pcb(uint32_t);
#endif
