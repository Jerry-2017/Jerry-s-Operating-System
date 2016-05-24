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

uint32_t fork()
{
	uint32_t id;
	asm("mov $0x6,%%ebx\n\tint $0x80":"=a"(id)::);
	return id;
}

uint32_t id;

uint32_t forkex()
{
	return id++;
}

void lock(int*i)
{
	while ((*i)==1);
	(*i)=1-(*i);
	return;
}

void unlock(int*i)
{
	(*i)=1-*i;
	return;
}
