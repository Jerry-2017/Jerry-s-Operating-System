[bits 16]
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
.c
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
; structure of read
;\\\\\\\\\\\\\\\\\\\\\\\;
DAPACK:
	db	0x10
	db	0
blkcnt:	dw	16			; int 13 resets this to # of blocks actually read/written
db_add:	dw	0x7C00		; memory buffer destination address (0:7c00)
	dw	0				; in memory page zero
d_lba:	dd	1			; put the lba to read in this spot
	dd	0				; more storage bytes only for big lba's ( > 4 bytes )
;-----------------------;