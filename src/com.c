#include "../include/com.h"
#include "../include/common.h"

void init_serial() {
	outb(COM_PORT + 1, 0x00);
	outb(COM_PORT + 3, 0x80);
	outb(COM_PORT + 0, 0x03);
	outb(COM_PORT + 1, 0x00);
	outb(COM_PORT + 3, 0x03);
   	outb(COM_PORT + 2, 0xC7);
	outb(COM_PORT + 4, 0x0B);
}

int is_serial_idle() {
	return inb(COM_PORT + 5) & 0x20;
}

void output(char* string)
{
	int cnt=0;
	while (string[cnt]!='\0' && cnt<MAX_STRING)
	{
		while (!is_serial_idle());
		outb(COM_PORT,string[cnt]);
	}
}	
		
