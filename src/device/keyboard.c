#include "include/common/common.h"
#include "include/common/printk.h"
#include "include/device/int.h"
#include "include/device/x86.h"
void keyboard_serv()
{
	uint32_t x=inb(0x60);
	printk("get key inf %x\n",x);
}

void keyboard_init()
{
	serv_addr((uint32_t)keyboard_serv,0x21);
}
