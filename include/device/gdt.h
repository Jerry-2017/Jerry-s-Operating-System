#ifndef __GDT_H__
#define __GDT_H__
void setgdt(uint32_t,uint32_t,uint32_t,uint32_t);
uint32_t getbase(uint32_t);
#define LOAD_SEG(ARG) asm("mov %%ax,%%es\n\tmov %%ax,%%ds\n\tmov %%ax,%%fs\n\tmov %%ax,%%gs"::"a"(ARG):);
#endif
