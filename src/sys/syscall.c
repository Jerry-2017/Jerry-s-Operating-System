#include "include/common/common.h"
#include "include/device/int.h"
#include "include/device/svga.h"
#include "include/common/printk.h"
#include "include/device/keyboard.h"
#include "include/sys/syscall.h"

void syscall_main(uint32_t intno, uint32_t ebx, uint32_t ecx, uint32_t edx)
{
	printk("into syscall intno:%x ebx:%x ecx:%x edx:%x\n",intno,ebx,ecx,edx);
	switch (intno)
	{
		case 1:		//fetch on keyboard return the keyno into address ebx
		{
			int keyno=get_key();
			*((uint32_t*)ebx)=keyno&0xff;
			break;
		}
		case 2:		//write the vga from addr dl:ebx of height ch wighth cl 
					// blocksize dh
		{
		}
		case 3:		//write the com port string dl:ebx
		{
		}
	}
}

void syscall_vga(uint32_t intno, uint32_t ebx, uint32_t ecx, uint32_t edx)
{
//	printk("into syscall intno:%x ebx:%x ecx:%x edx:%x\n",intno,ebx,ecx,edx);
	uint16_t height=((uint32_t) ecx)>>16;
	uint16_t weight=((uint32_t) ecx)&0xFFFF;
	uint16_t blocksize=((uint32_t)edx)>>16;
	uint32_t addr=ebx;
	cp_block(height,weight,blocksize,addr);
}

void syscall_init()
{
	serv_addr((uint32_t)syscall_main,0x80);
	serv_addr((uint32_t)syscall_vga,0x81);	

}
