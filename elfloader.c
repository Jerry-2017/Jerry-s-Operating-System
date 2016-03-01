#include "./include/io.h"
#include "./include/common.h"
#include "./include/elf.h"
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
	readsects((void*)dst,GAME_SECTORS,0x80);
	while (1)
	{
		uint32_t tp=load_elf(LOADING_ENTRY);
		//char ascode[32];
		//ssprintf(ascode,"jmpl %x",LOADING_ENTRY);
		asm("call *%%eax"::"a"(tp):);
	}
	return 0;
}

//void readsect(uint32_t lba,uint32_t count,uint32_t memaddr)
//{
//	asm("call 0x8800"::"a"(lba),"c"(count),"D"(memaddr):);
//}
