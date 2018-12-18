.PHONY:clean
clean: *.o
	rm *.o

.PHONY:build
build:2048.c
	gcc -std=c99 -g 2048.c -o 2048