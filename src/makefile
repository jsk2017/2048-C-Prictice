.PHONY:build
build:	2048.o myheader.o author.o
	gcc -std=c99 -g myheader.o author.o 2048.o  -o ../bin/2048

.PHONY:clean
clean: *.o 
	rm *.o

2048.o:	2048.c myheader.h
	gcc -c 2048.c

myheader.o:	myheader.c myheader.h
	gcc -c myheader.c

author.o: author.c author.h
	gcc -c author.c

