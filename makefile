.PHONY:clean
clean: *.o
	rm *.o

.PHONY:build
build:2048.c
	gcc -g 2048.c -o 2048