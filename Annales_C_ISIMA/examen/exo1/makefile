CC=gcc

all:exo1 main

exo1:exo1.o code.o  teZZt.o
	$(CC) -g -o exo1 exo1.o code.o teZZt.o -lm 
	@echo "Lancer le programme avec  ./exo1" 
main:main.o code.o  teZZt.o 
	$(CC) -g -o main main.o code.o teZZt.o -lm 
	@echo "Lancer le programme avec  ./main" 
../teZZt.o:teZZt.h teZZt.c
	$(CC) -g -c teZZt.c -o teZZt.o
exo1.o:exo1.c code.h 
	$(CC) -g -c exo1.c -g -Wall -Wextra
code.o:code.h code.c
	$(CC) -g -c code.c -g -Wall -Wextra
clean:
	rm -rf exo1 main code.o exo1.o teZZt.o main.o *.gch
