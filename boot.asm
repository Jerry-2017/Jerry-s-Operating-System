[bits 16]
%define VGA_MODE13_WIDTH 320
%define VGA_MODE13_HEIGHT 200

section .text
	global_start

_start:
	cli					; clear interruption
	
	mov ah, 24h
	mov al, 1
	int 15h				; open 20address gate 
	
	call mode13h
	mov es, 0xa0000	
	
	mov cx, 200			; iterative setting color
.a
	mov dx, 320
.b
	mov cl, 13			;
	dec dx, 1
	


	mov si, DAPACK		; address of "disk address packet"
	mov ah, 0x42		; AL is unused
	mov dl, 0x80		; drive number 0 (OR the drive # with 0x80)
	int 0x13
	;jc short .error

.loop
	jmp .loop

mode13h:
	mov ah, 0
	mov al, 0x13		£»320x200x8 bit [mode 0x13]
	int 0x10
	ret

;-----------------------;
;	renders pixel
;	cl = color ax = y bx = x
;	es:bp = buffer
;-----------------------;

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

_section .data
logo db 'Jerry @ Feb ,2016 copyright'


DAPACK:
	db	0x10
	db	0
blkcnt:	dw	16		; int 13 resets this to # of blocks actually read/written
db_add:	dw	0x7C00		; memory buffer destination address (0:7c00)
	dw	0		; in memory page zero
d_lba:	dd	1		; put the lba to read in this spot
	dd	0		; more storage bytes only for big lba's ( > 4 bytes )
