.PHONY	: commit clean debug gdb run
boot512b.img : boot.img mbrformat.o elfloader.s
	./mbrformat.o
run: boot512b.img
	sh ./run.sh
elfloader.s: elfloader.c
	gcc elfloader.c -o elfloader.o -fno-builtin -std=gnu11 -m32 -c && ld -o elfloadertp.o -Ttext 0x8000 -m \
	elf_i386 -nostdlib -e main elfloader.o && objcopy --strip-all --only-section=.text -S -O binary \
	elfloadertp.o elfloader.img && objdump -D -b binary -m i386 elfloader.img >elfloader.s
mbrformat.o:
	gcc -o mbrformat.o mbrformat.c
boot.img : boot.asm
	nasm -f bin -o boot.img boot.asm &&  objdump -D -b binary -m i8086 boot.img >boot.s

commit : 
	git add -A && git commit

clean :
	rm -f *.o *~ *.img *.s *.bin

QEMU_OPTIONS := -serial stdio #以标准输入输为串口(COM1)
QEMU_OPTIONS += -d int #输出中断信息
QEMU_OPTIONS += -monitor telnet:127.0.0.1:1111,server,nowait #telnet monitor

QEMU_DEBUG_OPTIONS := -S #启动不执行
QEMU_DEBUG_OPTIONS += -s #GDB调试服务器: 127.0.0.1:1234

GDB_OPTIONS := -ex "target remote 127.0.0.1:1234"
GDB_OPTIONS += -ex "symbol boot512b.img"
QEMU    := qemu-system-i386
GDB     := gdb

gdb:
	$(GDB) $(GDB_OPTIONS)

debug: 
	$(QEMU) $(QEMU_DEBUG_OPTIONS) $(QEMU_OPTIONS) boot512b.img



CFLAGS := -Wall -Werror -Wfatal-errors #开启所有警告, 视警告为错误, 第一个错误结束编译
CFLAGS += -MD #生成依赖文件
CFLAGS += -std=gnu11 -m32 -c #编译标准, 目标架构, 只编译
CFLAGS += -I . #头文件搜索目录
CFLAGS += -O0 #不开优化, 方便调试
CFLAGS += -fno-builtin #禁止内置函数
CFLAGS += -ggdb3 #GDB调试信息
GAME_OBJECTS := game.c

