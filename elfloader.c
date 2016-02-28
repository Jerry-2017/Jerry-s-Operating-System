#include "./include/io.h"
#include "./include/common.h"
#include "./include/elf.h"
#define LOADING_ENTRY 0X100000
#define GAME_SECTORS 0x10
void (*addr) (void);
int main()
{
	void *dst;
	dst=(void *)0x100000;
	readsect(dst,GAME_SECTORS);
	while (1)
	{
		uint32_t tp=load_elf(LOADING_ENTRY);
		addr=(void*)tp;
		addr();
	}
	return 0;
}
