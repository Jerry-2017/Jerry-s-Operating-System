#include "include/device/int.h"
#include "include/device/com.h"
#include "include/common/common.h"
#include "include/device/svga.h"
#include "include/device/timer.h"
#include "include/device/keyboard.h"
#include "include/common/printk.h"

void ioinit()
{
//	ioinit8259();
//	timer_init();
//	keyboard_init();
//	init_idt();
	printk("init io pass\n");
}

int main()
{
	ioinit();
	while (1)
	{
		printk("kernel\n");
	}
	return 0;
}
