[bits 32]
section .text:
	global _start
_start:
call  0x10:0x12345678
iret
ret
call label
iret
label:
ret
mov eax,0x1234
add esp,0x4
pushad
popad
mov bp,ss
push ds
push es
nop
push fs
nop
push gs
pop es
pop fs
nop
pog gs
nop
pop ds
nop
mov ss,bp

mov es,ax
mov fs,ax
mov gs,ax
