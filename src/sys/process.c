#include "include/sys/process.h"
#include "include/common/printkex.h"
void exit()
{
	asm("mov $0x3,%%ebx\n\tint $0x80":::"%ebx");
	return;
}

void sleep(uint32_t time)
{
	asm("mov $0x4,%%ebx\n\tint $0x80"::"c"(time):"%ebx");
	return;	
}

uint32_t fork()
{
	uint32_t __volatile__ id;
	asm __volatile__("pusha");
	asm __volatile__("mov $0x6,%%ebx\n\tint $0x80":"=a"(id)::"%ebx");
	asm __volatile__("popa");
	return id;
}

uint32_t open_semaphore()
{
	uint32_t __volatile__ sid=-1;
	asm("mov %%ds,%%dx\n\tint $0x80"::"c"((uint32_t)&sid),"b"(0x7));
	printkex("get semaphore sid:%x\n",sid);
	return sid;
}

void sem_wait(uint32_t sid)
{
	uint32_t sid1=sid;
	asm("int $0x80"::"c"(sid1),"b"(0x8));
//	printkex("sem_wait return\n");
	return;
}

void sem_post(uint32_t sid)
{
	uint32_t sid2=sid;
	asm("int $0x80"::"c"(sid2),"b"(0x9));
//	printkex("sem_post return\n");
	return;
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
