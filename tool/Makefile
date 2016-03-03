.PHONY: 
FILE1 = pizza
start: $(FILE1).jpg
	#convert $(file1).jpg $(FILE1).bmp
	#gcc bmp2raw.c -o bmp2raw.o
	#./bmp2raw.o $(FILE1).bmp
	convert \( $(FILE1).jpg  -channel R -separate \) \
	\( $(FILE1).jpg  -channel G -separate \) \
	\( $(FILE1).jpg  -channel B -separate \) -channel RBG -combine -depth 8 rgb:pizza.raw
	-rm ../res/*.raw
	mv *.raw ../res/

