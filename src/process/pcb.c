#include "include/common/common.h"
#include "include/process/pcb.h"
#include "include/device/gdt.h"
#include "include/common/printk.h"

pcb proc[MAX_PROC_NUM];
uint32_t cpcb_i;

void init_pcb()
{
	cpcb_i=0;
	int i;
	for (i=0;i<MAX_PROC_NUM;i++)
	{
		proc[i].is_used=0;
	}
}

int new_pcb(uint16_t dataseg,uint16_t codeseg,uint32_t off)
{
	int i;
	for (i=0;i<MAX_PROC_NUM;i++)	
	{
		if (proc[i].is_used==0)
		{
			proc[i].is_used=1;
			proc[i].dataseg=dataseg;
			proc[i].codeseg=codeseg;
			proc[i].ptr=&(proc[i].stack[MAX_STACK-1]);
			printk("choos ptr:%x\n",proc[i].ptr);
			asm __volatile__("mov %%esp,%%ebx\n\tmov %0,%%esp\n\tpush %%ecx\n\tpush $0xffffff\n\tpushf\n\tpush %%eax\n\tpush %%edx\n\tmov %%esp,%0\n\tmov %%ebx,%%esp":"=m"(proc[i].ptr):"m"(proc[i].ptr),"c"(dataseg),"a"(codeseg),"d"(off):"%ebx");
			return i;
		}
	}
	return -1;
}

void start_pcb(uint32_t no)
{	
	cpcb_i=no;
	uint32_t s=proc[no].dataseg;
	uint32_t ptr=(uint32_t)proc[no].ptr;
	printk("into start pcb no:%d datas:%x ptr:%x\n",no,s,ptr);
	asm __volatile__("mov %0,%%edx"::"m"(ptr));
	LOAD_SEG(s);
	asm __volatile__("mov %edx,%esp\n\tiret");
}

//void save_pcb();
