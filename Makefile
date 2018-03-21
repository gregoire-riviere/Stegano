stegano: stegano.o main.o
	gcc -g -o stegano stegano.o main.o

stegano.o : stegano.c
	gcc -g -o stegano.o -c stegano.c -W -Wall -ansi -pedantic

main.o: main.c stegano.h
	gcc -g -o main.o -c main.c -W -Wall -ansi -pedantic
