#include "include/common/common.h"
#ifndef __PCB_H__
#define __PCB_H__
#define MAX_STACK 1024
#define MAX_PROC_NUM 0x10
struct ProgramControlBlock{
	uint8_t stack[MAX_STACK];
	uint8_t* ptr;
	uint32_t extra;
	uint8_t is_used;
	uint32_t paddr;
	uint16_t dataseg;
	uint16_t codeseg;
	uint16_t stackseg;
	uint32_t esp;
};
typedef struct ProgramControlBlock pcb;
void sleep(uint32_t);
void pwait(uint32_t);
void init_pcb();
int get_pcb();
void set_pcb_ex(uint16_t index,uint32_t off);
void set_pcb(uint16_t index,uint32_t off,uint32_t esp);
void start_pcb(uint32_t);
void change_pcb();
void fork();
uint32_t pcb_paddr(uint32_t);
pcb proc[MAX_PROC_NUM];
uint32_t cpcb_i;
#endif
