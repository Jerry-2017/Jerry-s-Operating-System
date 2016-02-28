#ifndef __IO_H__
#define __IO_H__
#include "common.h"
void waitdisk(void);
void readsect(void *dst, uint32_t offset);
#endif
