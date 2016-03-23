#include "include/common/common.h"
#include "include/common/printk.h"
#include "include/device/int.h"
#include "include/device/x86.h"
#define BUFFER_LEN 0x200
uint32_t keyboard_buffer[BUFFER_LEN];
int s,e;
void keyboard_serv()
{
	uint32_t x=inb(0x60);
	if (e!=s)
	{
		keyboard_buffer[e]=x;
		e=(e+1)%BUFFER_LEN;
	}
	printk("get key inf %x\n",x);
}

uint32_t get_key()
{
	if (((s+1)%BUFFER_LEN)==e)
		return -1;
	s=(s+1)%BUFFER_LEN;
	return keyboard_buffer[s];
}

void keyboard_init()
{
	s=0;
	e=1;
	serv_addr((uint32_t)keyboard_serv,0x21);
}
