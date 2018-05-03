all: multiply filter emboss

multiply: clock.c multiply.c
	gcc -g -m32 -o multiply multiply.c clock.c

filter: clock.c bmp.c filter.c
	gcc -g -o filter filter.c bmp.c clock.c

emboss: clock.c bmp.c emboss.c
	gcc -g -m32 -o emboss emboss.c bmp.c clock.c

tests: multiplyTest filterTest embossTest

multiplyTest: multiply
	./multiply 700

filterTest: flowers.bmp filter
	./filter filter.txt flowers.bmp flowersBASE.bmp flowersOPT.bmp
	diff flowersBASE.bmp flowersOPT.bmp

embossTest: datsun.bmp emboss
	./emboss emboss.txt datsun.bmp datsunBASE.bmp datsunOPT.bmp
	diff datsunBASE.bmp datsunOPT.bmp

clean:
	rm -f multiply filter emboss
	rm -f datsunBASE.bmp datsunOPT.bmp
	rm -f flowersBASE.bmp flowersOPT.bmp
