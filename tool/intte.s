
intte.o:     file format binary


Disassembly of section .data:

00000000 <.data>:
   0:	9a 78 56 34 12 10 00 	lcall  $0x10,$0x12345678
   7:	cf                   	iret   
   8:	c3                   	ret    
   9:	e8 01 00 00 00       	call   0xf
   e:	cf                   	iret   
   f:	c3                   	ret    
  10:	b8 34 12 00 00       	mov    $0x1234,%eax
  15:	83 c4 04             	add    $0x4,%esp
  18:	60                   	pusha  
  19:	61                   	popa   
  1a:	66 8c d5             	mov    %ss,%bp
  1d:	1e                   	push   %ds
  1e:	06                   	push   %es
  1f:	90                   	nop
  20:	0f a0                	push   %fs
  22:	90                   	nop
  23:	0f a8                	push   %gs
  25:	07                   	pop    %es
  26:	0f a1                	pop    %fs
  28:	90                   	nop
  29:	65 90                	gs nop
  2b:	1f                   	pop    %ds
  2c:	90                   	nop
  2d:	8e d5                	mov    %ebp,%ss
  2f:	8e c0                	mov    %eax,%es
  31:	8e e0                	mov    %eax,%fs
  33:	8e e8                	mov    %eax,%gs
