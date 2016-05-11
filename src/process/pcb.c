#include "include/common/common.h"
#include "include/process/pcb.h"
#include "include/device/gdt.h"
#include "include/common/printk.h"
#include "include/process/schedule.h"
#include "include/device/tss.h"
#include "include/device/gdt.h"

pcb proc[MAX_PROC_NUM];
uint32_t cpcb_i;
//uint32_t id=0;

void init_pcb()
{
	cpcb_i=0;
	int i;
	for (i=1;i<MAX_PROC_NUM;i++)
	{
		proc[i].is_used=0;
		proc[i].paddr=0x1000000+i*0x2000000;
		proc[i].dataseg=0x28+0x3;
		proc[i].codeseg=0x30+0x3;
	}
	idle_no=0;
	uint32_t addr=(uint32_t)(void*)&idle;
	//printk("idle address %x\n",idle);
	proc[0].paddr=0x0;
	proc[0].dataseg=0x28+0x3;
	proc[0].codeseg=0x30+0x3;
//	proc[0].esp=0x17ffff;
	set_pcb(0x0,addr,0x17ffff);
	set_status(idle_no,5);
}

uint32_t pcb_paddr(uint32_t index)
{
	return proc[index].paddr;
}

int get_pcb()
{
	int i=allocate_slot();
	//set_pcb(i,off);
	return i;
}
void set_pcb_ex(uint16_t index,uint32_t off)
{
	set_pcb(index,off,0x1ffffff);
}
void set_pcb(uint16_t index,uint32_t off,uint32_t esp)
{
	int i=index;
	proc[i].esp=esp;
//	proc[i].dataseg=0x28+0x3;//dataseg;
//	proc[i].codeseg=0x30+0x3;//codeseg;
    uint32_t tp;
	proc[i].ptr=&(proc[i].stack[MAX_STACK-1]);
	printk("choos ptr:%x\n",proc[i].ptr);
	asm __volatile__("mov %%esp,%%ebx\n\tmov %0,%%esp\n\tpush %%ecx\n\tmov %2,%%ecx\n\tpush %%ecx\n\tpushf\n\tpush %%eax\n\tpush %%edx\n\tmov %%esp,%0\n\tmov %%ebx,%%esp":"=m"(proc[i].ptr),"=c"(tp):"m"(proc[i].esp),"c"(proc[i].dataseg),"a"(proc[i].codeseg),"d"(off):"%ebx");
	//printk("esp %x\n",tp);
//	printk("size %x!!!\n",-(proc[i].ptr-&(proc[i].stack[MAX_STACK-1])));
	return ;
}

void save_pcb()
{
	uint8_t *i=(uint8_t*)tss.esp0;
	uint8_t *j=&(proc[cpcb_i].stack[MAX_STACK-1]);
	int cnt=0;
	for	(;cnt<0x14;cnt++)
	{
		*(j--)=*(i--);
	}
	//printk("valid pcb\n");
	uint32_t off,codeseg,dataseg,esp;
	asm __volatile__("mov %%esp,%%ebx\n\tmov %3,%%esp\n\tpop %%edx\n\tpop %%eax\n\tpop %%ecx\n\tpop %%ecx\n\tmov %%ecx,%4\n\tpop %%ecx\n\tmov %%ebx,%%esp":"=d"(off),"=a"(codeseg),"=c"(dataseg):"m"(proc[cpcb_i].ptr),"m"(esp):"%ebx");
	printk("off %x codeseg %x dataseg %x esp %x\n",off,codeseg,dataseg,esp);
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
	 int i=cpcb_i;
	 cpcb_i=change_process(cpcb_i);
	 if (i==cpcb_i) return;
	 printk("new pcb is %d",cpcb_i);
//	 set_status(cpcb_i,0);
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
	set_status(no,0);
	setgdt(0x28,0x2,proc[no].paddr,0x2000000);
	setgdt(0x30,0x3,proc[no].paddr,0x2000000);
	cpcb_i=no;
	uint32_t s=proc[no].dataseg;
	uint32_t ptr=(uint32_t)proc[no].ptr;
//	printk("into start pcb no:%d datas:%x ptr:%x esp:%x\n",no,s,ptr,proc[no].esp);
	asm __volatile__("mov %0,%%edx"::"m"(ptr));
	LOAD_SEG(s);
	asm __volatile__("mov %edx,%esp\n\tiret");
}



