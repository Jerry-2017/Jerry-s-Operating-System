.PHONY: start1
FILE1 = pizza
start1:
	convert $(FILE1).jpg $(FILE1).bmp
	gcc bmp2raw.c -o bmp2raw.o
	./bmp2raw.o $(FILE1).bmp
	rm ../res/*.raw
	mv *.raw ../res/

