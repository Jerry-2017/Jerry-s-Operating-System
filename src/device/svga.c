#include "include/device/x86.h"
#include "include/common/printk.h"
#include "include/device/gdt.h"
#include "math.h"
#define SVGA_ADDR 0x79f0 
#pragma GCC push_options
#pragma GCC optimize("O3")

uint16_t vga_x,vga_y;
uint32_t svga_addr;
uint16_t pitch;
#define BLOCK_SIZE 0x08
#define MAX_Y 768
#define MAX_X 1024
#define PIXEL_SIZE(NUM) ((NUM)*3)
#define PIXEL_PHYADDR(X,Y,I) ((uint32_t)(Y) * pitch + (X) *3+ (I))
#define PIXEL_MEMADDR(X,Y,I) ((uint32_t)(Y) * vga_x *3+ (X) *3+ (I))

void vbe_set(uint16_t xres, uint16_t yres, uint16_t bpp)
{
	svga_addr=(*((uint32_t*)SVGA_ADDR));
	pitch=*((uint16_t*)(SVGA_ADDR+4));
	printk("The svga stream entry address is %x\nthe pitch is %x\n",svga_addr,pitch);	
	vga_x=xres;
	vga_y=yres;
}


void cp_block(uint16_t height,uint16_t weight,uint16_t blocksize,uint32_t addr,uint16_t ds) 
{
	//printk("vgax :%x pitch:%x\n",vga_x,pitch);
	uint32_t re_addr=PIXEL_SIZE(MAX_X*height+weight);
	uint32_t pa=svga_addr+re_addr;
	uint32_t ma=addr+re_addr;
	
	uint32_t xl=PIXEL_SIZE(blocksize);
	int i,j;
	uint32_t off=getbase(ds);
	ma+=off;
	//asm("mov %%ax,%%es":"=a"(ds)::);
	//printk("cp_blcok used h:%x w:%x blksz:%x addr:%x\n",height,weight,blocksize,addr);
//	printk("block h%x w%x, pa %x to ma %x\n",height,weight,pa,ma);
	for (i=0;i<blocksize;i++) 
	{
		for (j=0;j<xl;j++) 
		{
			//asm("movb %%es:(%%eax,%%ebx,1),(%%ecx,%%ebx,1)":"=a"(ma),"=b"(j),"=c"(pa)::);
			*((uint8_t*)(pa+j))=*((uint8_t*)(ma+j));
		}
		pa+=PIXEL_SIZE(MAX_X);
		ma+=PIXEL_SIZE(MAX_X);
	}
}
	

#pragma GCC pop_options
