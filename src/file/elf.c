#include "include/file/elf.h"
//#include "../include/io.h"

uint32_t load_elf(uint32_t loading_entry)
{
	struct ELFHeader *pelfhead=(void *)loading_entry;
	uint32_t entry=pelfhead->entry;
	uint32_t phoff=pelfhead->phoff;
	//uint32_t phentsize=pelfhead->phentsize;
	uint32_t phnum=pelfhead->phnum;
	struct ProgramHeader *pprghead=(void*)(loading_entry+phoff);
	uint32_t i,j;
	for (i=0;i<phnum;i++)
	{
		uint32_t offset=pprghead->off;
		uint32_t paddr=pprghead->paddr;
		uint32_t filesz=pprghead->filesz;
		uint32_t* ptr1=(void*)paddr;
		uint32_t* ptr2=(void*)(loading_entry+offset);
		uint32_t memsz=pprghead->memsz;
		for (j=0;j<filesz;j+=4)
			*(ptr1++)=*(ptr2++);
		for (;j<memsz;j+=4)
			*(ptr1++)=0;
		pprghead++;
	}
	return entry;
}
