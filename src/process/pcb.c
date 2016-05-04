#include "include/common/common.h"
#include "include/process/pcb.h"
#include "include/device/gdt.h"
#include "include/common/printk.h"
#include "include/process/schedule.h"
#include "include/device/tss.h"
#include "include/process/schedule.h"
#include "include/device/gdt.h"

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
	int i=allocate_slot();
	proc[i].dataseg=dataseg;
	proc[i].codeseg=codeseg;
	proc[i].ptr=&(proc[i].stack[MAX_STACK-1]);
	printk("choos ptr:%x\n",proc[i].ptr);
	asm __volatile__("mov %%esp,%%ebx\n\tmov %0,%%esp\n\tpush %%ecx\n\tpush $0xffffff\n\tpushf\n\tpush %%eax\n\tpush %%edx\n\tmov %%esp,%0\n\tmov %%ebx,%%esp":"=m"(proc[i].ptr):"m"(proc[i].ptr),"c"(dataseg),"a"(codeseg),"d"(off):"%ebx");
	return i;
}

void save_pcb()
{
	uint8_t *i=(uint8_t*)tss.esp0;
	uint8_t *j=&(proc[cpcb_i].stack[MAX_STACK-1]);
	for	(;j>=proc[cpcb_i].ptr;j--)
	{
		(*j)=(*i);
		i--;
	}
	return;
}

void sleep(uint32_t time)
{
	sch_sleep(cpcb_i,time);
	change_pcb();
}

void change_pcb()
{
	 save_pcb();
	 printk("old pcb is %d ",cpcb_i);
	 cpcb_i=change_process(cpcb_i);
	 printk("new pcb is %d ",cpcb_i);
	 start_pcb(cpcb_i);
}

void exit_pcb()
{
	release_slot(cpcb_i);
	change_pcb();
}

void fork()
{
	setgdt(0x38,0x2,0x4000000,0xffffff);
	setgdt(0x40,0x3,0x4000000,0xffffff);
	int i=0;
	uint8_t *ptr=(void*)0x2000000,*ptr1=(void*)0x4000000;

    for (;i<0x2000000;i++)
	{
		*(ptr1++)=*(ptr++);
	}
	save_pcb();
	proc[cpcb_i].dataseg=0x38+0x3;
	proc[cpcb_i].codeseg=0x40+0x3;
	int t=allocate_slot();
	cpcb_i=t;
	save_pcb();
	change_pcb();
}

void start_pcb(uint32_t no)
{
	start_process(no);
	cpcb_i=no;
	uint32_t s=proc[no].dataseg;
	uint32_t ptr=(uint32_t)proc[no].ptr;
	printk("into start pcb no:%d datas:%x ptr:%x\n",no,s,ptr);
	asm __volatile__("mov %0,%%edx"::"m"(ptr));
	LOAD_SEG(s);
	asm __volatile__("mov %edx,%esp\n\tiret");
}

