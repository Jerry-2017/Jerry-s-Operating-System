#include "stdio.h" 
#include "string.h"

#define maxn 512
#define sectors 0x2000
#define total (sectors)*maxn
#define GAME_START 0x10
int a[total];
void readfile(char * fname,int offset)
{
	FILE* fi=fopen(fname,"r");
	int cnt=0;
	while (!feof(fi))
	{
		a[cnt+offset]=fgetc(fi);
		cnt++;
	}
	fclose(fi);
	return;
}


int main()
{
	FILE* fo=fopen("boot512b.img","w");
	int i;
	for (i=0;i<total;i++)
	{
		a[i]=0x90;
	}
	readfile("boot.img",0);
	readfile("elfloader.img",512);
//	readfile("iofunc.img",512*5);
	readfile("game.o",512*GAME_START);
	readfile("./res/pizza.raw",0x21*512);
	a[510]=0x55;
	a[511]=0xaa;
//	resformat();
	for (i=0;i<total;i++)
		fprintf(fo,"%c",a[i]);
	fclose(fo);
}

