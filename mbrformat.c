#include "stdio.h" 
#include "string.h"

#define maxn 512
#define sectors 0x10
#define total (sectors+1)*maxn
int a[total];
void readfile(char * fname,int offset)
{
	FILE* fi=fopen(fname,"r");
	int cnt=0;
	int i;
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
	a[510]=0x55;
	a[511]=0xaa;
	for (i=0;i<total;i++)
		fprintf(fo,"%c",a[i]);
	fclose(fo);
}

