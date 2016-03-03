#include "stdio.h" 
#include "string.h"

#define maxn 512
#define sectors 0x2000
#define total (sectors)*maxn
#define GAME_START 0x10
char a[total];
void readfile(char * fname,int offset,int type)
{
	FILE* fi=fopen(fname,"rb");
	int cnt=0;
	int bias=0;
	while (!feof(fi))
	{
		if (type==1)
		{
			bias=2-cnt%3*2;
		}
		a[cnt+offset+bias]=fgetc(fi);
		cnt++;
	}
	fclose(fi);
	return;
}


int main()
{
	FILE* fo=fopen("boot512b.img","wb");
	int i;
	for (i=0;i<total;i++)
	{
		a[i]=0x90;
	}
	readfile("boot.img",0,0);
	readfile("elfloader.img",512,0);
//	readfile("iofunc.img",512*5);
	readfile("game.o",512*GAME_START,0);
	readfile("./res/pizza.raw",0x100*512,1);
	a[510]=0x55;
	a[511]=0xaa;
//	resformat();
	for (i=0;i<total;i++)
		fprintf(fo,"%c",a[i]);
	fclose(fo);
}

