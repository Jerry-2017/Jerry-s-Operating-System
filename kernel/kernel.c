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

#define GAME_SECTORS 0x300
#define GAME_LEN 0x500
#define PIC_LEN 0x2000
#define PIC_START 0x800
#define PROGRAM_START 0x1800000
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

void loadprog()
{
	readsects((void*)PROGRAM_START,GAME_SECTORS,GAME_LEN);
	readsects((void*)(0x2500000),PIC_START,PIC_LEN);
	uint32_t tp=load_elf(PROGRAM_START,0x2000000);
	setgdt(0x28,0x0,0x2000000,0xffffff);
	setgdt(0x30,0x1,0x2000000,0xffffff);
	asm __volatile__("mov %0,%%edx"::"r"(tp):);
	LOAD_SEG(0x28);
	asm __volatile__("push %%bx\n\tpush %%edx\n\tlret"::"b"(0x30):);
}

int main()
{
	ioinit();
	printk("kernel\n");
	while (1)
	{
		loadprog();
	}
	return 0;
}
