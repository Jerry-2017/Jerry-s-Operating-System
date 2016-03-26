#include "include/device/com.h"
#include "include/common/common.h"
void output_ex(char* string)
{
	//printk("output ex addr: %x\n",string);
	asm("mov %%ds,%%dx\n\tint $0x80"::"c"((uint32_t)string),"b"(0x2):);
	return;
}
