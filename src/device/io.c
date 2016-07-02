#include "include/common/common.h"
#include "include/device/x86.h"
#define SECTSIZE 512

void waitdisk(void)
{
    // wait for disk reaady
    while ((inb(0x1F7) & 0xC0) != 0x40);
        // do nothing;
}

void readsect(void *dst, uint32_t offset)
{
    // wait for disk to be ready
    waitdisk();

    outb(0x1F2, 1);     // count = 1
    outb(0x1F3, offset);    //address = offset | 0xe0000000
    outb(0x1F4, offset >> 8);
    outb(0x1F5, offset >> 16);
    outb(0x1F6, (offset >> 24) | 0xE0);
    outb(0x1F7, 0x20);  // cmd 0x20 - read sectors

    // wait for disk to be ready
    waitdisk();

    // read a sector
    insl(0x1F0, dst, SECTSIZE/4);
}

void readsects(void *dst, uint32_t offset, uint32_t count)
{
	int cnt=0;
	while (cnt<count)
	{
		readsect(dst+cnt*SECTSIZE,offset);
		offset++;
		cnt++;
	}
}

void writesect(uint32_t secno, const void *src, uint32_t nsecs)
{
	//assert(nsecs <= 256);

	waitdisk();

	outb(0x1F2, nsecs);
	outb(0x1F3, secno & 0xFF);
	outb(0x1F4, (secno >> 8) & 0xFF);
	outb(0x1F5, (secno >> 16) & 0xFF);
	outb(0x1F6, 0xE0 | ((0&1)<<4) | ((secno>>24)&0x0F));
	outb(0x1F7, 0x30);	// CMD 0x30 means write sector

	for (; nsecs > 0; nsecs--, src += SECTSIZE) {
		waitdisk();
		outsl(0x1F0, src, SECTSIZE/4);
	}

	return ;
}

void writesects(void *src,uint32_t  offset,uint32_t count)
{
	int cnt=0;
	while (cnt<count)
	{
		writesect(offset,src+cnt*SECTSIZE,1);
		offset++;
		cnt++;	
	}
	return ;
}

int fread(const char* fname,uint32_t addr)
{
   readsects((void*)0x1800000,0x300,0x500);
   return 0;
}

int finit()
{
   return 0;
}
