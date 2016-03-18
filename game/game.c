#include "include/device/int.h"
#include "include/device/com.h"
#include "include/common/common.h"
#include "include/common/printk.h"
#include "include/sys/display.h"
#include "include/device/svga.h"
#include "include/common/rvgs.h"
#include "include/device/timer.h"
#include "include/device/keyboard.h"
#include "include/sys/syscall.h"

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

void ioinit()
{
	ioinit8259();
	timer_init();
	keyboard_init();
	vbe_set(1024,768,24);
	syscall_init();
	init_idt();
	printk("init io pass\n");
}

void draw_circle(int bx,int by)
{
	int cnt=BLOCK;
	for (int i=bx;i<bx+2;i++)
	{
		line (i*1024/cnt,by*768/cnt,i*1024/cnt,(by+1)*768/cnt,0xF0FFF0,0x2);	
	}
	for (int i=by;i<by+2;i++)
	{
		line (bx*1024/cnt,i*768/cnt,(bx+1)*1024/cnt,i*768/cnt,0xF0FFF0,0x2);	
	}
}

int main()
{
	output("it's the start of Jerry's game, enjoy it\n");
	printk_test();	
	initperm();
	printk("init game pass\n");
	ioinit();
	//int cnt=BLOCK;
	for (int i=0;i<BLOCK*BLOCK;i++)
		draw(i);
//	draw_line();
	int sx=0,sy=0;
/*	for (int j=0;j<768;j++)
	{
		for (int i=0;i<1024;i++)
		{		
			point(i,j,*addr);
			addr=(uint32_t*)(((char*)addr)+3);
		}
	}	*/
	printk("draw pass\n");
	int state=1;
	int dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
	while (1)
	{
	//		72
	// 75    <   > 77
	// 		80
		draw_line();
		draw_circle(sx,sy);
		cp_image();
		int b=-1;
		while (!(b>=0 && b<=4))
		{
			b=get_key();
			switch(b)
			{
				case 75:
					b=0;break;
				case 77:
					b=1;break;
				case 72:
					b=2;break;
				case 80:
					b=3;break;
				case 0x9c:
					b=4;
			}
		}
		int tx=sx+dir[b][0];
		int ty=sy+dir[b][1];
		if (b==4) state=1-state;
		if (tx>=0 && ty>=0 && tx<BLOCK && ty<BLOCK)
		{
			if (state)
			{
				int t1=p[ty*BLOCK+tx];
				int t2=p[sy*BLOCK+sx];
				p[ty*BLOCK+tx]=t2;
				p[sy*BLOCK+sx]=t1;
				draw(ty*BLOCK+tx);
				draw(sy*BLOCK+sx);
			}
			sx=tx;
			sy=ty;
		}

	}
	return 0;
}
