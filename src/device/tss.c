#include "include/common/common.h"
#include "include/device/tss.h"
#include "include/device/gdt.h"

tss_entry_t tss;

void init_tss()
{
	int i;
	for (i=0;i<sizeof(tss);i++)
		*((uint8_t*)&tss)=0;
	tss.ss0=0x40;
	setgdt(0x40,0x5,0,0xffffffff);
	tss.ss = tss.ds = tss.es = tss.fs = tss.gs = 0x8+0x3;
	tss.cs=0x13;
	tss.esp0=0x1ffffff;
	setgdt(0x38,0x4,(uint32_t)&tss,sizeof(tss));
	asm("mov $0x38,%%ax\n\tltr %%ax":::);
}
