#include "include/file/elf.h"
#include "stdio.h"
#include "string.h"

#define maxn 0x10000
char a[maxn];
int main()
{
	printf("\n");
	printf("running elf header test program\n");
	FILE *fp=fopen("game.o","rb");
	int cnt=0;
	while (!feof(fp))
	{
		a[cnt++]=fgetc(fp);
	}
	
	struct ELFHeader *pelfhead=(void *)a;
	uint32_t entry=pelfhead->entry;
	uint32_t phoff=pelfhead->phoff;
//	uint32_t phentsize=pelfhead->phentsize;
	uint32_t phnum=pelfhead->phnum;
	struct ProgramHeader *pprghead=(void*)(a+phoff);
	int i=0;
	//printf("%d\n",phnum);
	for (i=0;i<phnum;i++)
	{
		uint32_t offset=pprghead->off;
		uint32_t paddr=pprghead->paddr;
		uint32_t vaddr=pprghead->vaddr;

		uint32_t filesz=pprghead->filesz;
		uint32_t memsz=pprghead->memsz;
/*		for (int i=0;i<filesz;i++)
			*(char *)(paddr+i)=*(char*)(loading_entry+offset+i);
		for (int i=filesz;i<memsz;i++)
			*(char *)(paddr+i)=0;*/
		printf("paddr:%x filesz:%x memsz:%x offset:%x vaddr:%x\n",paddr,filesz,memsz,offset,vaddr);
		pprghead++;
	}
	printf("entry: 0x%x\n",entry);
	return 0;
}
