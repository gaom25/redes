#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

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

/*void procpadre() // Como argumento deberia ir el nombre del archivo
{
	/* El padre abrira el archivo y leera las palabras a buscar */

	/* El archivo que se vaya a pasar habria que sacarlo del arreglo de
	argumentos */

/*	FILE *fd;
	char palabras[200];

	fd=fopen(“palabras.txt”, "r");
	if (fd==NULL){
		//perror("No se pudo abrir el archivo");
		print("No se pudo abrir el archivo");
		exit(1);
	}
	
	// Mientras no haya finalizado el archivo, sigue leyendo
	while(feof(fd)!=0){
		fgets(palabras, 200, fd); // El peo es que guarda tambien el \n, ¿como se evita?
		// Aqui iria una llamada a lo que hace los hijos
	}	
}*/
