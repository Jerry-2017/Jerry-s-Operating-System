#ifndef __COMMON_H__
#define __COMMON_H__
#define MAX_STRING 256
#define true 1
#define false 0
typedef char bool;


typedef long  s32;
typedef signed short s16;
typedef signed char  s8;
typedef signed long  const sc32;  /* Read Only */
typedef signed short const sc16;  /* Read Only */
typedef signed char  const sc8;   /* Read Only */
typedef volatile signed long  vs32;
typedef volatile signed short vs16;
typedef volatile signed char  vs8;
typedef volatile signed long  const vsc32;  /* Read Only */
typedef volatile signed short const vsc16;  /* Read Only */
typedef volatile signed char  const vsc8;   /* Read Only */

typedef unsigned long long   uint64_t;
typedef unsigned int  uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char  uint8_t;

typedef unsigned long  const uc32;  /* Read Only */
typedef unsigned short const uc16;  /* Read Only */
typedef unsigned char  const uc8;   /* Read Only */
typedef volatile unsigned long  vu32;
typedef volatile unsigned short vu16;
typedef volatile unsigned char  vu8;
typedef volatile unsigned long  const vuc32;  /* Read Only */
typedef volatile unsigned short const vuc16;  /* Read Only */
typedef volatile unsigned char  const vuc8;   /* Read Only */
#include "math.h"
#include "stdarg.h"
#include "include/device/x86.h"
#endif
