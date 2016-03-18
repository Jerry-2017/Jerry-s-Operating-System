#include "include/device/int.h"
#include "include/device/com.h"
#include "include/common/common.h"
#include "include/device/svga.h"
#include "include/device/timer.h"
#include "include/device/keyboard.h"

void ioinit()
{
	ioinit8259();
	timer_init();
	keyboard_init();
	init_idt();
	printk("init io pass\n");
}
