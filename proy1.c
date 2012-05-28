#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void procpadre(int argc, char *argv[]);
void titulo_pal(int argc, char *argv[]);
void comprobacion(int argc, char *argv[]);
int prochijo(int argc, char *argv[], char palabras[]);

int main (int argc, char *argv[])
{
	 
comprobacion(argc, argv);

printf("args: %d \n", argc);
printf("array[0]: %s \n", argv[0]);
printf("array[1]: %s \n", argv[1]);
printf("array[2]: %s \n", argv[2]);
printf("arch entrada: %s \n", argv[argc-2]);

}

/* Funcion que comprueba el pase de argumentos */
void comprobacion(int argc, char *argv[])
{
	
	if (!(argc > 1 && argc < 6)) {
		printf("Numero de argumentos invalidos\n");
		exit(1);
	}
	
	if(strcmp(argv[1],"-h") == 0) {
		if ((argv[2]) != NULL) {
			printf("-h es excluyente de las otras opciones\n");
			exit(1);
		}
	}
	
	int i;
	for(i = 1; i < argc; i++) {
		if (strcmp(argv[i],"-f") == 0 || strcmp(argv[i],"-w") == 0 ) {
			if (argv[i+2] == NULL) {
				printf("Falta archivo de entrada\n");
				exit(1);
			} else {
				if (strcmp(argv[i+2],"-w") == 0 || strcmp(argv[i+2],"-f") == 0) {
					printf("Las opciones -w y -f son excluyentes\n");
					exit(1);
				}
			}	
		}
	}

	int num = atoi(argv[2]);
	if (num < 1) {
		printf("n debe ser un entero mayor o igual que 1\n");
		exit(1);
	}	
	
}
	
/* Funcion del proceso padre */
void procpadre(int argc, char *argv[])
{
	FILE *fd;
	char palabras[50], titulo[50], pal_buscar[50];
	int filed[2];
	int i, n, hpid, num;
		
	/* Nombre del archivo que contiene las palabras queda en titulo[]*/
	for (i = 1; i < argc; i++) {
		if (strcmp(argv[i],"-f") == 0) {
			strcpy(titulo, argv[i+1]);
		}
	}
	
	/* Numero de procesos concurrentes */
	for (i = 1; i < argc; i++) {	
		if (strcmp(argv[i],"-n") == 0) {
			n = atoi(argv[i+1]);
		} else {
			n = 1;
		}	
	}	

	/* Abre el archivo de palabras a buscar*/
	fd = fopen(titulo, "r");
	if (fd == NULL) {
		printf("No se pudo abrir el archivo\n");
		exit(1);
	}
	
	/*pipe(filed); 
	 * ESTO CREO QUE DEBERIA ESTAR DENTRO DEL WHILE, PORQUE
	 * EL PADRE DEBERIA TENER UN PIPE DIFERENTE A TRAVES DEL CUAL COMUNICARSE
	 * CON CADA HIJO */
				
	
	/* El proceso padre comienza a leer las palabras y se las pasa a los 
	 * procesos hijos, a traves del pipe */
	while(!feof(fd)) {
		fscanf(fd, "%s", palabras);
		for(i=0; i<n; i++) {
			hpid=fork();
			if (hpid < 0) {
				printf("Error al crear el proceso hijo\n");
				exit(1);
			}
			if (hpid != 0) {	// Si es el proceso padre
				pipe(filed);
				close(filed[0]);
				write(filed[1], palabras, strlen(palabras) + 1);
				close(filed[1]);
			} else {		// Si es el proceso hijo
				close(filed[1]);
				read(filed[0], pal_buscar, 50);
				close(filed[0]);
				
				/* NO SE SI PONER QUE LA FUNCION DEL HIJO RETORNE EL NUMERO DE 
				 * VECES QUE ENCONTRO LA PALABRA Y LUEGO ENVIARSELA AQUI
				 * POR UN PIPE AL PROCESO PADRE, PERO NO SE SI ESE PIPE ES
				 * EL MISMO QUE USO PARA RECIBIR LA PALABRA DEL PADRE, NI SE
				 * COMO HACER PARA QUE EL PADRE LEA LA PALABRA ENVIADA POR EL HIJO */
				num = prochijo(argc, argv, pal_buscar);
				/* SERIA ESCRIBIR num EN UN PIPE Y QUE EL PADRE LO LEA */
						
			}			
		}
	}		
}		

/* Funcion del proceso hijo */
/* NO SE SI DEBERIA HACERSE ASI, RETORNANDO UN ENTERO QUE ES EL NUMERO
 * DE VECES QUE ENCONTRO LA PALABRA */
int prochijo(int argc, char *argv[], char palabras[])
{
	FILE *fd;
	char entrada[50], pal_archivo[50];
	int i=0;
	
	/* Obtiene el archivo de entrada y lo abre*/
	strcpy(entrada, argv[argc-2]);
		
	fd = fopen(entrada, "r");
	if (fd == NULL) {
		printf("No se pudo abrir el archivo\n");
		exit(1);
	}
	
	/* Lee las palabras del archivo y las compara con la palabra a buscar
	 * enviada por el padre */
	while(!feof(fd)) {
		fscanf(fd, "%s", pal_archivo);
		if (strcmp(pal_archivo, palabras) == 0)
		{
			i++;
		}
	}	
	
	return i;
}
