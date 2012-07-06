CC = gcc
OBJS = funciones.o

pargrep: hilos.c funciones.o
			$(CC) $(OBJS) -o $@ hilos.c -lpthread
			
funciones.o: funciones.c funciones.h
			$(CC) -c funciones.c funciones.h
	
		
