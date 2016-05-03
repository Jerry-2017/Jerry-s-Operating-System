#include "include/sys/process.h"

void exit()
{
	asm("mov $0x3,%%ebx\n\tmov %%ds, %%dx\n\tint $0x80":::"%ebx");
	return;
}

void sleep(uint32_t time)
{
	asm("mov $0x4,%%ebx\n\tint $0x80"::"c"(time):);
	return;	
}
