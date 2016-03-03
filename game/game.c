#include "include/device/com.h"
#include "include/common/common.h"
#include "include/common/printk.h"
#include "include/device/svga.h"
int main()
{
	output("it's the start of Jerry's game, enjoy it\n");
	vbe_set(1024,768,24);
	printk_test();	
	uint32_t* addr=(uint32_t*)(0x100000+(0x100-0x10)*512);
	for (int j=0;j<768;j++)
	{
		for (int i=0;i<1024;i++)
		{
			point(i,j,*addr);
			addr=(uint32_t*)(((char*)addr)+3);
		}
	}
	cp_image();
	while (1)
	{
		//printk("%d\n",*((uint32_t*)0xe000000));

	}
	return 0;
}
