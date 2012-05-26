#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void procpadre(int argc, char *argv[]);
void titulo_pal(int argc, char *argv[]);
int comprobacion(int argc, char *argv[]);

int main (int argc, char *argv[])
{
	
/* n es el numero de procesos concurrentes */
int i,j;
int n = 0;
pid_t hpid;
 
j = comprobacion(argc, argv);
for(i=0; i<n; i++)
{
	hpid=fork();
	if (hpid < 0) {
		perror("Error al crear el proceso hijo");
		exit(1);
	}	
}

if (hpid==0)
{
	/* Aqui se pondria a los hijos a buscar las palabras */
}
}

/* Funcion que comprueba el pase de argumentos */
int comprobacion(int argc, char *argv[])
{

	if (argc>6 || argc<1)
	{
		printf("Numero de argumentos invalidos\n");
		return(0);
	}
	
	if(strcmp(argv[1],"-h") == 0)
	{

		if (argv[2]!=NULL)
		{
			printf("-h es excluyente de las otras opciones\n");
			return(0);
		}
	}
	
	int i;
	for(i=1; i<=argc; i++)
	{
		if (strcmp(argv[i],"-f") == 0 || strcmp(argv[i],"-w") == 0 )
		{
			if (argv[i+2]==NULL)
			{
				printf("Argumentos invalidos\n");
				return(0);
			} else {
				if (strcmp(argv[i+2],"-w") == 0 || strcmp(argv[i+2],"-f") == 0)
				{
					printf("Las opciones -w y -f son excluyentes\n");
					return(0);
				}
			}	
		}
	}
	
	// Comprobar que n > 0 int num=(int)(argv[3]);
	
}
	
/* Funcion del proceso padre */
void procpadre(int argc, char *argv[])
{
	/* El padre abrira el archivo y leera las palabras a buscar */

	FILE *fd;
	char palabras[50];
	
	// Nombre del archivo que contiene las palabras quedara en titulo[]
	int i;
	char titulo[20];
	for(i=1; i<=argc; i++)
	{
		if (strcmp(argv[i],"-f") == 0)
		{
			strcpy(titulo, argv[i+1]);
		}
	}

	fd=fopen(titulo, "r");
	if (fd==NULL){
		printf("No se pudo abrir el archivo");
		exit(1);
	}
	
	// Mientras no haya finalizado el archivo, sigue leyendo
	while(feof(fd)!=0){
		fscanf(fd, "%s", palabras);
		// Aqui iria una llamada a lo que hace los hijos, pasandole la palabra
	}	
}		
