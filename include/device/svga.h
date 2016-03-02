#ifndef __SVGA_H__
#define __SVGA_H_
#include "include/common/common.h"
#define SVGA_ADDR 0xe0000000
void vbe_set(uint16_t xres, uint16_t yres, uint16_t bpp);
//void vbe_write(uint16_t index,uint16_t  value);
void cp_image(uint32_t*);
#endif
