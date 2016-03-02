#include "include/device/com.h"
#include "include/common/common.h"
#include "include/common/printk.h"
#include "include/device/svga.h"
int main()
{
	output("it's the start of Jerry's game, enjoy it\n");
	vbe_set(1024,768,24);
	printk_test();	
	while (1)
	{
		cp_image((void*)(0x100000+0x20*512));
		//printk("%d\n",*((uint32_t*)0xe000000));

	}
	return 0;
}
