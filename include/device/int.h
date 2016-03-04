#include "include/common/common.h"
#ifndef __INT_H__
#define __INT_H__
#pragma pack (1)

#define IDT_ADDR 0x0
void init_idt();
void ioinit8259();
void serv_addr(uint32_t addr,uint32_t num);

struct int_gate{
	uint16_t offset_l;
	uint16_t seg;
	union {
		uint16_t attr; //0x8e00
		struct{
			uint16_t de:13;
			uint16_t dpl:2;
			uint16_t p:1;
		};
	};
	uint16_t offset_h;
};

struct idtr{
	uint16_t limit;
	uint32_t base;
};

#pragma pack (4)
#endif 
