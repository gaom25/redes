CCFLAGS= -o
CC = gcc

pargrep: makefile
	  $(CC) $(CCFLAGS) $@ pargrep.c

clean:
	/bin/rm *.o registro
