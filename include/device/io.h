#ifndef __IO_H__
#define __IO_H__
#include "include/common/common.h"
void waitdisk(void);
void readsect(void *dst, uint32_t offset);
void readsects(void *dst, uint32_t offset, uint32_t count);
#endif
