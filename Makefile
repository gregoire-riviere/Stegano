steno: steno.o main.o
	gcc -o steno steno.o main.o

steno.o : steno.c
	gcc -o steno.o -c steno.c -W -Wall -ansi -pedantic

main.o: main.c steno.h
	gcc -o main.o -c main.c -W -Wall -ansi -pedantic
