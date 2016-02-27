.PHONY	: boot512b.img commit
boot512b.img : boot.img mbrformat.c
	./mbrformat.o && sh ./run.sh
mbrformat.o:
	gcc -o mbrformat.o mbrformat.c
boot.img : boot.asm
	nasm -f bin -o boot.img boot.asm

commit : 
	git add -A && git commit

CFLAGS := -Wall -Werror -Wfatal-errors #开启所有警告, 视警告为错误, 第一个错误结束编译
CFLAGS += -MD #生成依赖文件
CFLAGS += -std=gnu11 -m32 -c #编译标准, 目标架构, 只编译
CFLAGS += -I . #头文件搜索目录
CFLAGS += -O0 #不开优化, 方便调试
CFLAGS += -fno-builtin #禁止内置函数
CFLAGS += -ggdb3 #GDB调试信息
GAME_OBJECTS := game.c
game.o : $(GAME_OBJECTS)
