[bits 16]
org 07c00h 				;segment address 0x07c00
%define VGA_MODE13_WIDTH 320
%define VGA_MODE13_HEIGHT 200

section .text
	global _start

_start:
	cli					; clear interruption
	
;-----------------------;
;open a20 gate
;\\\\\\\\\\\\\\\\\\\\\\\;
	mov ah, 24h
	mov al, 1
	int 15h				; open 20address gate 
;-----------------------;


;-----------------------;
;setting initial image
;\\\\\\\\\\\\\\\\\\\\\\\;
	call mode13h
	mov ax, 0xa000
	mov es, ax			; the start point of vga memory
	mov bp, 0x0
	mov ax, 200-1		; iterative setting color
.a:
	mov bx, 320-1
	mov cl, 0x50
	xor dl, dl			; set dl to 0
	test ax,ax
	jz .d
	dec ax
.b:
	inc dl				; blue color
	cmp dl, 20			; select the bueatiful line of palette
	jnz .c
	xor dl, dl
	inc cl
.c:
	call pixel
	test bx,bx
	jz .a
	dec bx
	jmp .b
.d:	
;-----------------------;


;-----------------------;
;load the first 0x16 sectors into memory
;\\\\\\\\\\\\\\\\\\\\\\\;
	mov si, DAPACK		; address of "disk address packet"
	mov ah, 0x42		; AL is unused
	mov dl, 0x80		; drive number 0 (OR the drive # with 0x80)
	int 0x13
	;jc short .error
;-----------------------;

;-----------------------;
;load idt table
;\\\\\\\\\\\\\\\\\\\\\\\;
	lidt [REG_IDT]
	sidt [TEMP]
;-----------------------;

;-----------------------;
;load gdt table
;\\\\\\\\\\\\\\\\\\\\\\\;
	mov cx, [ADDR_GDT]
	mov [STYPE],BYTE 10000010B	;SYS DATA
	call gdtload
	mov cx, [ADDR_GDT]
	add cx, 0x08
	mov [STYPE],BYTE 10001010B	;SYS CODE
	call gdtload
	mov cx, [ADDR_GDT]
	add cx, 0x10
	mov [STYPE],BYTE 11100010B	;USER DATA
	call gdtload
	mov cx, [ADDR_GDT]
	add cx, 0x18
	mov [STYPE],BYTE 11101010B	;USER CODE
	call gdtload
	lgdt [REG_GDT]
	sgdt [TEMP]
	mov ax, 0x0
	jmp 0x0:f
f:
	mov ax, 0x8
	mov ds, ax
	mov ss, ax
	mov es, ax
;-----------------------;



;-----------------------;
;change into protected mode
;\\\\\\\\\\\\\\\\\\\\\\\;
mov eax, cr0
or ax, 0x1
mov esp, 0x8000000		;128 MB
mov cr0, eax
;dw 0xea66 				;ljmp
;dd 0x8000				;protected mode entry
;dw 0x0					;seg selector
jmp 0x8000
dw 0x0
;-----------------------;

.loop:
	jmp .loop			; stop it here
	
;-----------------------;
;setting vga mode to 13h
;\\\\\\\\\\\\\\\\\\\\\\\;
mode13h:
	mov ah, 0
	mov al, 0x13		;320x200x8 bit [mode 0x13]
	int 0x10
	ret
;-----------------------;

;-----------------------;
;load one gdt entry to [cx]
;\\\\\\\\\\\\\\\\\\\\\\\;
gdtload:
	pusha
	mov di, 8
.e:
	dec di
	mov bx, SEGDP
	mov ax,	[bx+di]
	mov bx, cx
	mov [bx+di], ax
	test di, di
	jnz .e
	popa
	ret
;-----------------------;


;-----------------------;
;	renders pixel
;	cl = color ax = y bx = x
;	es:bp = buffer
;\\\\\\\\\\\\\\\\\\\\\\\;
pixel:
	; [x + y * width] = col
	pusha
	mov di, VGA_MODE13_WIDTH
	mul di ; ax = y * width
	add ax, bx ; add x
	mov di, ax
	mov byte [es:bp + di], cl ; plot pixel
	popa
	ret
;-----------------------;


section .data
logo db 'Jerry @ Feb ,2016 copyright',0

;-----------------------;
; regeister of gdt
;\\\\\\\\\\\\\\\\\\\\\\\;
REG_GDT:
	dw 0x200			; size of gdt 256 entries
ADDR_GDT:
	dd 0x7e00			; address of gdt
;-----------------------;

;-----------------------;
; regeister of gdt
;\\\\\\\\\\\\\\\\\\\\\\\;
REG_IDT:
	dw 0x200			; size of gdt 256 entries
ADDR_IDT:
	dd 0x0000			; address of gdt
;-----------------------;

;-----------------------;
; Segment Descriptor
;\\\\\\\\\\\\\\\\\\\\\\\;
SEGDP:
	dw 0xffff			; segment limit 0-15
SEGBASE:
	dw 0x0
	db 0x0				; segment base 23-07c00h
STYPE:
	db 10000010B		; 4  excute 3 consistent 2 read 1 visit
	;0010 data seg  1010  exec	;
	db 0xcf				; g d + seng limit 16-13
	db 0x0				; seg base 24-31
;-----------------------;
	
TEMP:
DD 0x0
DW 0x0
	

;-----------------------;
; structure of read
;\\\\\\\\\\\\\\\\\\\\\\\;
DAPACK:
	db	0x10
	db	0
blkcnt:	dw	16			; int 13 resets this to # of blocks actually read/written
db_add:	dw	0x8000		; memory buffer destination address (0:8000)
	dw	0				; in memory page zero
d_lba:	dd	1			; put the lba to read in this spot
	dd	0				; more storage bytes only for big lba's ( > 4 bytes )
;-----------------------;