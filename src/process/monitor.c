#include "include/common/common.h"
#include "include/common/printk.h"
#include "include/device/timer.h"

void kernel_wakeup(uint32_t time)
{
//	printk("wake up time %x ms\n",time);
	return;
}
	
void init_monitor()
{
	wakeupreg(kernel_wakeup);
}
