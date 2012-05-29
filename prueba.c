#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int prochijo(int argc, char *argv[], char palabras[]);

int main (int argc, char *argv[]) {

	FILE *fd;
	char palabras[50], titulo[50], pal_buscar[50];
	int filed[2];
	int i, n=2, hpid, num;

	/* Busca el archivo de las palabras */
	for (i = 1; i < argc; i++) {
		if (strcmp(argv[i],"-f") == 0) {
			strcpy(titulo, argv[i+1]);
		}
	}
	
	fd = fopen(titulo, "r");
	if (fd == NULL) {
		printf("No se pudo abrir el archivo\n");
		exit(1);
	}
	
	while(!feof(fd)) {
		fscanf(fd, "%s", palabras);
		printf("la palabra: %s \n", palabras);
		//for(i=0; i<n; i++) {
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
				//printf("las veces que sale %s es %d \n", pal_buscar, num);
				/* SERIA ESCRIBIR num EN UN PIPE Y QUE EL PADRE LO LEA */
						
			}			
		//}
	}
	
	
}

int prochijo(int argc, char *argv[], char palabras[])
{
	FILE *fd;
	char entrada[50], pal_archivo[50];
	int i=0, pidh, pidp;
	
	if (strcmp(palabras, "NOMAS") == 0) {
		pidh = getpid();
		pidp = getppid();
		printf("Mi PID es %d, el PID de mi padre es %d", pidh, pidp);
		// FALTARIA IMPRIMIR TODAS LAS PALABRAS QUE BUSCO
	}	
		
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
		if (strcmp(pal_archivo, palabras) == 0) {
			i++;
		}
	}	
	
	return i;
}	
