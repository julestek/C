CC=gcc

all:exo2 main

exo2:exo2.o code.o  teZZt.o
	$(CC) -g -o exo2 exo2.o code.o teZZt.o -lm 
	@echo "Lancer le programme avec  ./exo2" 
main:main.o code.o  teZZt.o 
	$(CC) -g -o main main.o code.o teZZt.o -lm 
	@echo "Lancer le programme avec  ./main" 
../teZZt.o:teZZt.h teZZt.c
	$(CC) -g -c teZZt.c -o teZZt.o
exo2.o:exo2.c code.h 
	$(CC) -g -c exo2.c -g -Wall -Wextra
code.o:code.h code.c
	$(CC) -g -c code.c -g -Wall -Wextra
clean:
	rm -rf exo2 main code.o exo2.o teZZt.o main.o *.gch
