#include "include/device/com.h"
#include "include/common/common.h"

void output_ex(char* string)
{
	asm("mov $0x2,%%ebx\n\tint $0x80"::"c"((uint32_t)string):"%ebx");
}
