#ifndef __DISPLAY_H__
#define __DISPLAY_H_
#include "include/common/common.h"
#define SVGA_ADDR 0xe0000000
//void vbe_write(uint16_t index,uint16_t  value);
void cp_image();
void point(uint32_t,uint32_t,uint32_t);
void line(uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t);
#endif
