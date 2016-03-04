#include "include/device/int.h"
#include "include/device/x86.h"
#include "include/common/printk.h"

#define IO_PIC1 0x20
#define IO_PIC2 0xA0
#define IRQ_OFFSET 0x20
#define IRQ_SLAVE 2
#define PIC_EOI		0x20

#define MAX_INT 256
#define JMP_CODE_LEN 0x20
#define SERVICE_BASE 0x10000
uint32_t idt[MAX_INT][2];
uint32_t intpro[MAX_INT];

void (*f) (void);
bool error[MAX_INT]={0,0,0,0,0,0,0,0,
					 1,0,1,1,1,1,1,0,
					 0,1,0,0,0,0,0,0,
					 0,0,0,0,0,0,1,0,
					 0,0};
void idt_setting();
void serv_addr(uint32_t addr,uint32_t num);
void rawservice();
void rawexception();
void PIC_sendEOI(unsigned char irq); 

void int_set(struct int_gate * ptr,uint32_t offset,uint16_t seg, uint8_t dpl)
{
	ptr->offset_l=offset&0xffff;
	ptr->offset_h=(offset>>16)&0xffff;
	ptr->seg=seg;
	ptr->attr=0x8e00;
	ptr->dpl=dpl&0x3;
}
	
void fill(uint32_t src,uint32_t dst, uint32_t len)
{
	uint32_t i=0;
	for (;i<len;i++)
	{
		*((uint8_t*)dst)=*((uint8_t*)src);
		dst++;
		src++;
	}
}
void idtz()
{
	int i=0;
	for (;i<MAX_INT;i++)
		intpro[i]=0x0;
}
void init_idt()
{
	//fill idt table
	idt_setting();
	uint32_t tp_addr=IDT_ADDR;
	uint32_t i,j;
/*	for (i=0;i<MAX_INT;i++)
		if (i!=0x20)
			serv_addr((uint32_t)rawexception,i); 
	serv_addr((uint32_t)rawservice,0x21); */
	for (i=0;i<MAX_INT;i++)
	{
		for (j=0;j<2;j++)
		{
			*((uint32_t*)tp_addr)=idt[i][j];
			tp_addr+=4;
		}
	}
	
	//fill service addr
	for (i=0;i<MAX_INT;i++)
	{
		uint32_t saddr=SERVICE_BASE+i*JMP_CODE_LEN;
		if (i<0x20 || i>0x20+15)//intpro[i]==0)
		{
			char asm_code[JMP_CODE_LEN]="\xcf";
			fill((uint32_t)asm_code,saddr,0x1);	
		}
		else
		{
			char asm_code[JMP_CODE_LEN]="\x83\xc4\x04"				//add esp,0x4
										"\x60"	//pushad
										"\xb8\x00\x00\x00\x00"
										"\x9a\x00\x00\x00\x00\x10\x00" //lcall 0x10: addr ret far needed or pop first
										"\x83\xc4\x04"
										"\x61"		//popad
										"\xcf";							// iret
			if (error[i]==0) 
			{
				*((uint16_t*)(asm_code))=0x9090;
				*((uint8_t*)(asm_code+2))=0x90;
			}
			*((uint32_t*)(asm_code+5))=i;
			if (i>=0x20 && i<=0x20+15)
				*((uint32_t*)(asm_code+10))=(uint32_t)rawservice;//intpro[i];
			else
				 *((uint32_t*)(asm_code+10))=(uint32_t)rawexception;
			fill((uint32_t)asm_code,saddr,JMP_CODE_LEN);
		}
	}

	//set idtr
	struct idtr reg;
	reg.base=IDT_ADDR;
	reg.limit=0x100*0x8;
	__asm__ volatile("lidt (%%eax)\n\tsti"::"a"(&reg));
}

void idt_setting()
{
	int i=0;
	struct int_gate *tp;
	for (i=0;i<MAX_INT;i++)
	{
		idt[i][0]=0;
		idt[i][1]=0;
		if (1 || (i>=8 && i<=9))
		{
			tp=(void*)idt[i]; //timer int
			int_set(tp,SERVICE_BASE+JMP_CODE_LEN*i,0x10,0x0);
		}
	}
}


void serv_addr(uint32_t addr,uint32_t num)
{
	intpro[num]=addr;
}

void  rawservice()
{
	uint32_t intno;
	asm("":"=a"(intno)::);
	if (intno!=0x20)
		printk("receive int %x\n",intno);
	if (intpro[intno]!=0)
	{
		f=(void*)intpro[intno];
		(*f)();
	}
	if (intno>=0x20 && intno<=0x20+15)
	{
		intno-=0x20;
		PIC_sendEOI(intno);
	}
}

void  rawexception()
{
	uint32_t intno;
	asm("":"=a"(intno)::);
	printk("int %x receive exception\n",intno);
}

void ioinit8259()
{
	// modify interrupt masks


	// Set up master (8259A-1)

	// ICW1:  0001g0hi
	//    g:  0 = edge triggering, 1 = level triggering
	//    h:  0 = cascaded PICs, 1 = master only
	//    i:  0 = no ICW4, 1 = ICW4 required
	outb(IO_PIC1, 0x11);

	// ICW2:  Vector offset
	outb(IO_PIC1+1, IRQ_OFFSET);

	// ICW3:  bit mask of IR lines connected to slave PICs (master PIC),
	//        3-bit No of IR line at which slave connects to master(slave PIC).
	outb(IO_PIC1+1, 1 << IRQ_SLAVE);

	// ICW4:  000nbmap
	//    n:  1 = special fully nested mode
	//    b:  1 = buffered mode
	//    m:  0 = slave PIC, 1 = master PIC
	//    (ignored when b is 0, as the master/slave role
	//    can be hardwired).
	//    a:  1 = Automatic EOI mode
	//    p:  0 = MCS-80/85 mode, 1 = intel x86 mode
	outb(IO_PIC1+1, 0x1);

	// Set up slave (8259A-2)
	outb(IO_PIC2, 0x11);              // ICW1
	outb(IO_PIC2 + 1, IRQ_OFFSET + 8);// ICW2
	outb(IO_PIC2 + 1, IRQ_SLAVE);     // ICW3
	// NB Automatic EOI mode doesn't tend to work on the slave.
	// Linux source code says it's "to be investigated".
	outb(IO_PIC2 + 1, 0x01);          // ICW4

	// OCW3:  0ef01prs
	//   ef:  0x = NOP, 10 = clear specific mask, 11 = set specific mask
	//    p:  0 = no polling, 1 = polling mode
	//   rs:  0x = NOP, 10 = read IRR, 11 = read ISR
	outb(IO_PIC1, 0x68);             /* clear specific mask */
	outb(IO_PIC1, 0x0a);             /* read IRR by default */

	outb(IO_PIC2, 0x68);             /* OCW3 */
	outb(IO_PIC2, 0x0a);             /* OCW3 */
	
	outb(IO_PIC1 + 1, 0xF0);
	outb(IO_PIC2 + 1, 0xFF);
}

void PIC_sendEOI(unsigned char irq)
{
	if(irq >= 8)
		outb(IO_PIC2,PIC_EOI);	
	outb(IO_PIC1,PIC_EOI);
}
