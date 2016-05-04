#include "include/common/common.h"
#include "include/common/printk.h"
#include "include/device/timer.h"
#include "include/process/pcb.h"
#include "include/process/schedule.h"
void kernel_wakeup(uint32_t time)
{
//	printk("wake up time %x ms\n",time);
	if (monitor_flag)
		monitor_call();
	return;
}
	
void init_monitor()
{
	wakeupreg(kernel_wakeup);
}
