.PHONY	: commit clean debug gdb run elfloader.o start
boot512b.img : start boot.img mbrformat.o elfloader.s game.o iofunc.img
	./mbrformat.o
start:
	make -C ./src

game.o : game.c
	gcc game.c -m32 -o game.o
run: boot512b.img
	sh ./run.sh
elfloader.o: elfloader.c
	gcc elfloader.c -o elfloader.o -fno-builtin -std=gnu11 -m32 -c
elfloader.s: elfloader.o 
	ld -o elfloadertp.o -Ttext 0x8000 -m elf_i386 -nostdlib -e main elfloader.o ./src/io.o ./src/elf.o && \
	objcopy --strip-all --only-section=.text -S -O binary elfloadertp.o elfloader.img && \
	objdump -D -b binary -m i386 elfloader.img > elfloader.s
mbrformat.o:
	gcc -o mbrformat.o mbrformat.c
boot.img : boot.asm
	nasm -f bin -o boot.img boot.asm &&  objdump -D -b binary -m i8086 boot.img >boot.s

iofunc.img : iofunc.asm
	nasm -f bin -o iofunc.img iofunc.asm &&  objdump -D -b binary -m i386 iofunc.img >iofunc.s


commit : 
	git add -A && git commit

clean :
	find . -name "*.o"  | xargs rm -f
	find . -name "*.d"  | xargs rm -f
	find . -name "*.d.*"  | xargs rm -f
	find . -name "*.swp"  | xargs rm -f
	rm -f -r *.o *~ *.img *.s *.bin *.d.* *.d

gdb:
	$(GDB) $(GDB_OPTIONS)

debug: 
	$(QEMU) $(QEMU_DEBUG_OPTIONS) $(QEMU_OPTIONS) boot512b.img

QEMU_OPTIONS := -serial stdio #以标准输入输为串�?COM1)
QEMU_OPTIONS := -m 256
QEMU_OPTIONS += -d int #输出中断信息
QEMU_OPTIONS += -monitor telnet:127.0.0.1:1111,server,nowait #telnet monitor

QEMU_DEBUG_OPTIONS := -S #启动不执�?
QEMU_DEBUG_OPTIONS += -s #GDB调试服务�? 127.0.0.1:1234

GDB_OPTIONS := -ex "target remote 127.0.0.1:1234"
GDB_OPTIONS += -ex "symbol boot512b.img"
QEMU    := qemu-system-i386
GDB     := gdb
