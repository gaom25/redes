CCFLAGS= -o
CC= gcc
OBJS= pila.o

directorio: $(OBJS)
			$(CC) $(OBJS) $(CCFLAGS) $@ directorio.c
pila.o: pila.c pila.h
		$(CC) -c pila.c
clean:
		/bin/rm *.o directorio
