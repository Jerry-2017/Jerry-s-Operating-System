#include "include/common/common.h"
#define GDT_ENTRY 0x7e00

void setgdt(uint32_t no,uint32_t type,uint32_t base,uint32_t limit)
{
	// P DEL :2 S E ED/C W/R A
	uint8_t typearr[7]={	0x92,		//ring 0 data write allow 10010010
					0x9a,		//ring 0 code read allow 10011010
					0xf2,		//ring 3 data
					0xfa,		//ring 3 code
					0x89,
					//edited to add stack
					0x96,	//ring 0 stack write allow 10010110
					0xf6	// ring 3 stack
};	
	uint8_t* ps=(void*)(GDT_ENTRY+((no>>3)<<3));
	*((uint16_t*)ps)=(uint16_t)(limit&0xffff);
	*((uint16_t*)(ps+2))=(uint16_t)base&0xffff;
	*(ps+4)=(uint8_t)((base>>16)&0xff);
	*(ps+5)=typearr[type];
	if (type!=4) 
		*(ps+6)=0xc0|((limit>>16)&0xf);  
	else
		*(ps+6)=((limit>>16)&0xf);
	*(ps+7)=(base>>24);
}

uint32_t getbase(uint32_t no)
{
     no=no&0xffff;
	 uint8_t* ps=(void*)(GDT_ENTRY+((no>>3)<<3));
	 uint32_t base=(((uint32_t)(*(ps+7)))<<24)|(*((uint16_t*)(ps+2)));
	 return base;
}

