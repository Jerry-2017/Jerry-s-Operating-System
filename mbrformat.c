#include "stdio.h" 
#include "string.h"

#define maxn 512
#define sectors 0x10
#define total (sectors+1)*maxn
int a[total];
int main()
{
	FILE* fi=fopen("boot.img","r");
	FILE* fo=fopen("boot512b.img","w");
	int cnt=0;
	int i;
	while (!feof(fi) && cnt <maxn)
	{
		a[cnt]=fgetc(fi);
		cnt++;
	}
	for (i=cnt;i<maxn;i++)
	{
		a[i]=0x90;
	}
	a[510]=0x55;
	a[511]=0xaa;
	for (i=maxn;i<sectors*maxn;i++)
	{
		a[i]=0x0;
	}
	for (i=0;i<total;i++)
		fprintf(fo,"%c",a[i]);
	fclose(fi);
	fclose(fo);
}

