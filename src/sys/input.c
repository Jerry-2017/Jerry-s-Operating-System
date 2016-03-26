#include "include/common/common.h"
#include "include/common/printk.h"

uint32_t get_keyex()
{
	volatile uint32_t keyc=0;
	asm("mov $0x1,%%ebx\n\tmov %%ds,%%dx\n\tint $0x80"::"c"((uint32_t)&keyc):"%ebx");
//	printk("get keyc addr: %x  :%x\n",&keyc,keyc);
	return keyc;
}

