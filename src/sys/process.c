#include "include/sys/process.h"

void exit()
{
	asm("mov $0x3,%%ebx\n\tint $0x80":::);
	return;
}

void sleep(uint32_t time)
{
	asm("mov $0x4,%%ebx\n\tint $0x80"::"c"(time):);
	return;	
}
