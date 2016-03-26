#define SVGA_ADDR 0x79f0 
#pragma GCC push_options
#pragma GCC optimize("O3")
#include "include/device/x86.h"
#include "include/common/printkex.h"
#include "math.h"
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
//uint32_t svga_addr;
//uint16_t pitch;
#define BLOCK_SIZE 0x20
#define MAX_Y 768
#define MAX_X 1024
#define PIXEL_PHYADDR(X,Y,I) PIXEL_MEMADDR(X,Y,I)//((uint32_t)(Y) * pitch + (X) *3+ (I))
#define PIXEL_MEMADDR(X,Y,I) ((uint32_t)(Y) * vga_x *3+ (X) *3+ (I))
static bool vga_page[MAX_X/BLOCK_SIZE][MAX_Y/BLOCK_SIZE];
static char vga_buffer[MAX_Y*MAX_X*3];
/*void vbe_write(uint16_t index,uint16_t  value)
{
   outw(VBE_DISPI_IOPORT_INDEX, index);
   outw(VBE_DISPI_IOPORT_DATA, value);
}*/

// xres 1024 yres 768 bpp 32bit : 0x00RRGGBB
void dirty(uint32_t,uint32_t);
void point(uint32_t,uint32_t,uint32_t);
void line(uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t);

void init_display()
{
	int i,j;
	vga_x=1024;
	vga_y=768;
	for (i=0;i<MAX_X/BLOCK_SIZE;i++)
		for (j=0;j<MAX_Y/BLOCK_SIZE;j++)	
			vga_page[i][j]=1;
}

void dirty (uint32_t x,uint32_t y)
{
	vga_page[x/BLOCK_SIZE][y/BLOCK_SIZE]=1;
}

void point (uint32_t x, uint32_t y, uint32_t color)
{
	if (!(x>=0 && x<vga_x && y>=0 && y<vga_y))
		return;
	dirty(x,y);	
	uint32_t i;
	for (i=0;i<3;i++)
	{
		vga_buffer[PIXEL_MEMADDR(x,y,i)]=color;
		color>>=8;
	}
}

#pragma GCC optimize("O0")
void cp_block_ex(uint32_t bx,uint32_t by)
{
	by*=BLOCK_SIZE;
	bx*=BLOCK_SIZE;
	uint32_t ecx=(by<<16)|(bx&0xffff);
	uint32_t ebx=(uint32_t)vga_buffer;
	volatile uint32_t edx;
	asm __volatile__("mov %%ds,%%dx":"=d"(edx)::);
	edx=(BLOCK_SIZE<<16)|(edx&0xffff);
//	printkex("into cp_block_ex\n");
	asm __volatile__("int $0x81"::"c"(ecx),"b"(ebx),"d"(edx):);
}
#pragma GCC optimize("O3")


void cp_image()
{
	int i,j;
	//printkex("cpimage page addr %x\n",(uint32_t)vga_page);
	for (i=0;i<vga_y/BLOCK_SIZE;i++)
	{
		for (j=0;j<vga_x/BLOCK_SIZE;j++)
		{
			if (vga_page[j][i]!=0)
			{
				vga_page[j][i]=0;
				cp_block_ex(j,i);
			}
		}
	}
}

void line(uint32_t x1,uint32_t y1,uint32_t x2,uint32_t y2,uint32_t color,uint32_t breadth)
{
	uint32_t i,j;
	if (x1==x2) 
	{
		if (y1>y2) {
			y1+=y2;
			y2=y1-y2;
			y1=y1-y2;
		}
		for (i=x1-breadth;i<=x1+breadth;i++)
		{
			for (j=y1;j<=y2;j++)
				point(i,j,color);
		}
	}
	else if (y1==y2) 
	{
		if (x1>x2) {
			x1+=x2;
			x2=x1-x2;
			x1=x1-x2;
		}
		for (i=y1-breadth;i<=y1+breadth;i++)
		{
			for (j=x1;j<=x2;j++)
				point(j,i,color);
		}
	}
	else
	{
		double vt=(double)(y2-y1)/(x2-x1);
		double l=sqrt(1+vt*vt);
		double vtx=1/l;
		double vty=vt/l;

		double vttx=-vt/l;
		double vtty=vtx;

		uint32_t li=round(sqrt((y2-y1)*(y2-y1)+(x2-x1)*(x2-x1)));
		for (i=0;i<li;i++)
		{
			double cx=x1+vtx*i;
			double cy=y1+vty*i;
			for (j=0;j<breadth;j++)
			{
				double cx1=j*vttx;
				double cy1=j*vtty;
				point(round(cx+cx1),round(cy+cy1),color);
				point(round(cx-cx1),round(cy-cy1),color);
			}
		}
	}
}
#pragma GCC pop_options
