# Makefile for my project

static: main.o libstatic.a
	gcc -o binary main.o -L. -lstatic

main.o: main.c
	gcc -c main.c

libstatic.a: revert_string.o
	ar cr libstatic.a revert_string.o

revert_string.o: revert_string.c
	gcc -c revert_string.c

clean:
	rm -f *.o *.a binary
