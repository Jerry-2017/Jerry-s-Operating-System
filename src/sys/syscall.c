#include "include/common/common.h"
#include "include/device/int.h"
#include "include/device/svga.h"
#include "include/common/printk.h"
#include "include/device/keyboard.h"
#include "include/sys/syscall.h"
#include "include/device/com.h"
#include "include/device/gdt.h"
#include "include/process/pcb.h"

void syscall_main(uint32_t intno, uint32_t choice, uint32_t ecx, uint32_t edx)
{
//	printk("into syscall intno:%x ebx:%x ecx:%x edx:%x\n",intno,choice,ecx,edx);
	switch (choice)
	{
		case 1:		//fetch on keyboard return the keyno into address ebx
		{
			uint32_t keyno=get_key()&0xffff;
			uint32_t off=getbase(edx);
			//asm("mov %%ax,%%es\n\tmov %%ebx,%%es:(%%ecx)\n\tmov %%es,%%ds":"=a"(ds),"=b"(keyno&0xffff),"=c"(ecx)::);
			*((uint32_t*)(ecx+off))=keyno;
			if (keyno!=0xffff) printk("keyc is %x\n",keyno);
			break;
		}
		case 2:		// output string through com ecx addr of string
		{
			uint32_t off=getbase(edx);
			//printk("edx: %x off :%x no: %x\n",edx,off,edx);
			output((char*)(off+ecx));
			break;
		}
		case 4:		//sleep ecx ms
		{
			printk("sleep call %dms\n",ecx);
			sleep(ecx);
			break;
		}
		case 5:   
		{		//refresh
			printk("into 0x80 5func:\n");
			change_pcb();
			break;
		}
	}
}

void syscall_vga(uint32_t intno, uint32_t ebx, uint32_t ecx, uint32_t edx)
{
	//write the vga from addr dl:ebx of height ch wighth cl
	 // blocksize dh 
	//printk("into syscall intno:%x ebx:%x ecx:%x edx:%x\n",intno,ebx,ecx,edx);
	uint16_t height=((uint32_t) ecx)>>16;
	uint16_t weight=((uint32_t) ecx)&0xFFFF;
	uint16_t blocksize=((uint32_t)edx)>>16;
	uint16_t ds=edx&0xffff;
	uint32_t addr=ebx;
	cp_block(height,weight,blocksize,addr,ds);
}

void syscall_init()
{
	serv_addr((uint32_t)syscall_main,0x80);
	serv_addr((uint32_t)syscall_vga,0x81);	
}
