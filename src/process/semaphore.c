#include "include/common/common.h"
#include "include/common/printk.h"
#define MAX_SEMAPHORE_NUM 0x200
static uint32_t __volatile__ semaphore[MAX_SEMAPHORE_NUM];
static uint32_t len1=0;

bool p(uint32_t sid)
{
	uint32_t __volatile__ test=0;
	asm __volatile__("mov $0x0,%%ebx\n\txchg %%ebx,%1":"=b"(test):"m"(semaphore[sid]):);
//	printk("sid %x value %x test %x\n",sid,semaphore[sid],test);
	return test;
}

void v(uint32_t sid)
{
/*	uint32_t test;
	asm __volatile__("mov %2,%%ebx\n\tmov $0x1,%%eax\n\txchg %%eax,%%ebx":"=b"(test),"=a"(semaphore[sid]):"b"(semaphore[sid]):"%eax","%ebx");
	return 1-test;*/
//	printk("sid %x release\n",sid);
	semaphore[sid]=1;
	return;
}

uint32_t open_semaphore()
{
	semaphore[len1]=1;	
	len1+=1;
	return len1-1;
}
