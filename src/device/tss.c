#include "include/common/common.h"
#include "include/device/tss.h"
#include "include/device/gdt.h"

tss_entry_t tss;

void init_tss()
{
	tss.ss0=0x8;
	tss.esp0=0xffffff;
	setgdt(0x38,0x4,(uint32_t)&tss,sizeof(tss));
	asm("mov $0x38,%%ax\n\tltr %%ax":::);
}
