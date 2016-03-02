#include "include/device/x86.h"
#include "include/common/printk.h"
#define SVGA_ADDR 0x79f0 
/*#define VBE_DISPI_IOPORT_INDEX			0x01CE
#define VBE_DISPI_IOPORT_DATA			0x01CF
#define VBE_DISPI_INDEX_ID				0x0
#define VBE_DISPI_INDEX_XRES			0x1
#define VBE_DISPI_INDEX_YRES			0x2
#define VBE_DISPI_INDEX_BPP				0x3
#define VBE_DISPI_INDEX_ENABLE			0x4
#define VBE_DISPI_INDEX_BANK			0x5
#define VBE_DISPI_INDEX_VIRT_WIDTH		0x6
#define VBE_DISPI_INDEX_VIRT_HEIGHT		0x7
#define VBE_DISPI_INDEX_X_OFFSET		0x8
#define VBE_DISPI_INDEX_Y_OFFSET		0x9

#define VBE_DISPI_DISABLED				0x00
#define VBE_DISPI_ENABLED				0x01
#define VBE_DISPI_GETCAPS				0x02
#define VBE_DISPI_8BIT_DAC				0x20
#define VBE_DISPI_LFB_ENABLED			0x40
#define VBE_DISPI_NOCLEARMEM			0x80
*/
uint16_t vga_x,vga_y;
uint32_t svga_addr;
uint16_t pitch;
/*void vbe_write(uint16_t index,uint16_t  value)
{
   outw(VBE_DISPI_IOPORT_INDEX, index);
   outw(VBE_DISPI_IOPORT_DATA, value);
}*/

// xres 1024 yres 768 bpp 32bit : 0x00RRGGBB

void vbe_set(uint16_t xres, uint16_t yres, uint16_t bpp)
{
	svga_addr=*((uint32_t*)SVGA_ADDR);
	pitch=*((uint16_t*)SVGA_ADDR+4); 
	printk("The svga stream entry address is %x\n",svga_addr);	
	vga_x=xres;
	vga_y=yres;
/*	vga_x=xres;
	vga_y=yres;
	vbe_write(VBE_DISPI_INDEX_ENABLE, VBE_DISPI_DISABLED);
	vbe_write(VBE_DISPI_INDEX_XRES, xres);
	vbe_write(VBE_DISPI_INDEX_YRES, yres);
	vbe_write(VBE_DISPI_INDEX_BPP, bpp);
	vbe_write(VBE_DISPI_INDEX_ENABLE, VBE_DISPI_ENABLED | VBE_DISPI_LFB_ENABLED);   */
}

void cp_image(uint32_t *addr)
{
	int total=(int)vga_x*vga_y*3/4;
	uint32_t *taddr=(uint32_t*)svga_addr;
	int c=0;
	for (int i=0;i<total;i++)
	{
		if (c++==vga_x) {
			c=0;
			taddr+=pitch/4;
		}
		if (c>100)
			*(taddr++)=*(addr++);

	}
}
