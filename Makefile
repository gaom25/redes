CC = gcc

all: UsoDisco

UsoDisco: UsoDisco.o pila.o
	$(CC) UsoDisco.o pila.o -g -o UsoDisco

UsoDisco.o: UsoDisco.c pila.h
	$(CC) -c UsoDisco.c

pila.o: pila.c pila.h
	$(CC) -c pila.c

clean:
	rm *.o UsoDisco
