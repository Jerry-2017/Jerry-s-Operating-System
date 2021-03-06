#include "include/device/int.h"
#include "include/device/com.h"
#include "include/common/common.h"
#include "include/device/svga.h"
#include "include/device/timer.h"
#include "include/device/keyboard.h"
#include "include/common/printk.h"
#include "include/file/elf.h"
#include "include/device/io.h"
#include "include/device/gdt.h"
#include "include/sys/syscall.h"
#include "include/device/tss.h"
#include "include/process/pcb.h"
#include "include/process/monitor.h"
#include "include/process/schedule.h"
#include "include/file/file.h"

#define GAME_SECTORS 0x300
#define GAME_LEN 0x500
#define PIC_LEN 0x2000
#define PIC_START 0x800
#define PROGRAM_START 0x1800000

//static int now_pcb=0;
void ioinit()
{
	ioinit8259();
	timer_init();
	keyboard_init();
	vbe_set(1024,768,24);
	syscall_init();
	init_idt();
	printk("init io pass\n");
}

void procinit()
{
	init_monitor();
	schedule_init();
	init_pcb();
        finit();
}

void loadprog()
{
//08 sys data 10 sys code
	//readsects((void*)PROGRAM_START,GAME_SECTORS,GAME_LEN);
        fread("Prog.o",PROGRAM_START);
	//readsects((void*)(0x3000000),PIC_START,PIC_LEN);
	int no=get_pcb();
	uint32_t addr=pcb_paddr(no);
	printk("load process into addr %x slot %x\n",addr,no);
	uint32_t tp=load_elf(PROGRAM_START,addr);
//	setgdt(0x28,0x2,0x2000000,0xffffff);
//	setgdt(0x30,0x3,0x2000000,0xffffff);
	init_tss();
	set_pcb_ex(no,tp);
	printk("program slot %d\n",no);
/*
	asm __volatile__("mov %0,%%edx"::"r"(tp):);
	LOAD_SEG(0x28+0x3);
	//asm __volatile__("push %%bx\n\tpush %%edx\n\tlret"::"b"(0x30+0x3):);
	asm __volatile__("push $0x2b\n\tpush $0xffffff\n\tpushf\n\tpush %%ebx\n\tpush %%edx\n\tiret"::"b"(0x30+0x3):); */
	start_pcb(no);
}

int main()
{
	setgdt(0x40,0x5,0,0xffffffff);
	asm ("mov $0x40,%%ax\n\tmov %%ax,%%ss":::"%eax");
	ioinit();
	procinit();
	printk("kernel\n");
	while (1)
	{
		loadprog();
	}
	return 0;
}
