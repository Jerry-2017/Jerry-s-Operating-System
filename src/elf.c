#include "../include/elf.h"
#include "../include/io.h"

uint32_t load_elf(uint32_t loading_entry)
{
	struct ELFHeader *pelfhead=(void *)loading_entry;
	uint32_t entry=pelfhead->entry;
	uint32_t phoff=pelfhead->phoff;
	uint32_t phentsize=pelfhead->phentsize;
	uint32_t phnum=pelfhead->phnum;
	for (int i=0;i<phnum;i++)
	{
		struct ProgramHeader *pprghead=(void*)(loading_entry+phoff+i*phentsize);
		uint32_t offset=pprghead->off;
		uint32_t vaddr=pprghead->vaddr;
		uint32_t filesz=pprghead->filesz;
		//uint32_t memsize=pprghead->memsz;
		for (int i=0;i<filesz;i++)
			*(char *)(vaddr+i)=*(char*)(loading_entry+offset+i);
	}
	return entry;
}
