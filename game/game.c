#include "include/device/int.h"
#include "include/device/com.h"
#include "include/common/common.h"
#include "include/common/printk.h"
#include "include/device/svga.h"
#include "include/common/rvgs.h"
#include "include/device/timer.h"
#include "include/device/keyboard.h"

#define VGAX 1024
#define VGAY 768
#define BLOCK 5
#define REAL_ADDR2(x,y) (((y)*VGAX+(x))*3)
#define REAL_ADDR3(x,y,c) (point((x),(y),(c)))
#define MARK_ADDR4(bx,by,x,y) REAL_ADDR2((bx)*(VGAX/BLOCK)+(x),(by)*(VGAY/BLOCK)+(y))
#define MARK_ADDR5(bx,by,x,y,c) REAL_ADDR3((bx)*(VGAX/BLOCK)+(x),(by)*(VGAY/BLOCK)+(y),c)
uint32_t addr=(0x100000+(0x100-0x10)*512);
int p[BLOCK*BLOCK];
void initperm()
{
	int cnt=BLOCK;
	int pl=cnt*cnt;
	for (int i=0;i<pl;i++)
		p[i]=-1;
	printk("rand:");
	for (int i=0;i<pl;i++)
	{
		int x=(Equilikely(0,pl-i)&0xff)%(pl-i)+1;
		printk("%x ",x);
		int j=-1;
		while (x!=0 && j<pl)
		{
			j++;
			if (p[j]==-1) x--;
		}
		p[j]=i;
	}
	printk("\n");
}

void draw(int i)
{
	uint32_t x,y;
	int b=p[i];
	int ix=i%BLOCK;
	int iy=i/BLOCK;
	int bx=b%BLOCK;
	int by=b/BLOCK;
	printk("%x block addr %x -> %x new block addr %x\n",i,MARK_ADDR4(ix,iy,0,0),b,(addr+MARK_ADDR4(bx,by,0,0)));
	for (y=0;y<VGAY/BLOCK;y++)
	{
		uint32_t dsx=ix*(VGAX/BLOCK);
		uint32_t dsy=iy*(VGAY/BLOCK)+y;
		uint32_t ss=addr+(bx*(VGAX/BLOCK)+(by*(VGAY/BLOCK)+y)*VGAX)*3;
		for (x=0;x<VGAX/BLOCK;x++)
		{
			point(dsx++,dsy,*((uint32_t*)ss));
			ss+=3;
		}
	}
}

void draw_line()
{
	int cnt=BLOCK;
	for (int i=0;i<cnt;i++)
	{
		line (i*1024/cnt,0,i*1024/cnt,768,0x111111,0x2);	
	}
	for (int i=0;i<cnt;i++)
	{
		line (0,i*768/cnt,1024,i*768/cnt,0x111111,0x2);	
	}
}

int main()
{
	output("it's the start of Jerry's game, enjoy it\n");
	vbe_set(1024,768,24);
	printk_test();	
	initperm();
	printk("init pass\n");
	//int cnt=BLOCK;
	for (int i=0;i<BLOCK*BLOCK;i++)
		draw(i);
	draw_line();
/*	for (int j=0;j<768;j++)
	{
		for (int i=0;i<1024;i++)
		{		
			point(i,j,*addr);
			addr=(uint32_t*)(((char*)addr)+3);
		}
	}	*/
	printk("draw pass\n");

	cp_image();
	ioinit8259();
	timer_init();
	keyboard_init();
	init_idt();
	printk("init idt pass\n");

	while (1)
	{
		//printk("%d\n",*((uint32_t*)0xe000000));
	//	printk("running\n");

	}
	return 0;
}
