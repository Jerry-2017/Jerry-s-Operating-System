FILE1 = pizza
$(FILE1).raw: $(FILE1).jpg testasm
	#convert $(file1).jpg $(FILE1).bmp
	#gcc bmp2raw.c -o bmp2raw.o
	#./bmp2raw.o $(FILE1).bmp
	-convert \( $(FILE1).jpg  -channel R -separate \) \
	\( $(FILE1).jpg  -channel G -separate \) \
	\( $(FILE1).jpg  -channel B -separate \) -channel RBG -combine -depth 8 rgb:pizza.raw
	-rm ../res/*.raw
	-cp *.raw ../res/
FILE2=intte
testasm: $(FILE2).asm
	nasm  -o $(FILE2).o $(FILE2).asm &&  objdump -D -b binary -m i386 $(FILE2).o > $(FILE2).s

