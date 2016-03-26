#include "./include/device/io.h"
#include "./include/common/common.h"
#include "./include/file/elf.h"
#include "./include/device/gdt.h"
//#include "string.h"
#define LOADING_ENTRY 0x100000
#define GAME_SECTORS 0x10
//void (*addr) (void);
//void readsect(uint32_t lba,uint32_t count,uint32_t memaddr);

int main()
{
	uint32_t dst;
	dst=LOADING_ENTRY;
//	readsect(GAME_SECTORS,0x20,dst);
	readsects((void*)dst,GAME_SECTORS,0x2000);
	while (1)
	{
		uint32_t tp=load_elf(LOADING_ENTRY,0x1000000); //16mb
		setgdt(0x28,0x0,0x1000000,0xffffff);
		setgdt(0x30,0x1,0x1000000,0xffffff);
		asm __volatile__("mov %0,%%edx"::"r"(tp):);
		LOAD_SEG(0x28);
		//char ascode[32];
		//ssprintf(ascode,"jmpl %x",LOADING_ENTRY);
		asm __volatile__("push %%bx\n\tpush %%edx\n\tlret"::"b"(0x30):);
	}
	return 0;
}

//void readsect(uint32_t lba,uint32_t count,uint32_t memaddr)
//{
//	asm("call 0x8800"::"a"(lba),"c"(count),"D"(memaddr):);
//}
