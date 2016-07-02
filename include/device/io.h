#ifndef __IO_H__
#define __IO_H__
#include "include/common/common.h"
void waitdisk(void);
void readsect(void *dst, uint32_t offset);
void readsects(void *dst, uint32_t offset, uint32_t count);
void writesect(uint32_t,const void*,uint32_t);
void writesects(void *,uint32_t,uint32_t);
int fread(const char*,uint32_t);
int finit();
#endif
