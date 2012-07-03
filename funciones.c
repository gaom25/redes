#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/* Funcion que busca una palabra en un archivo.
 * Devuelve un entero con el numero de veces que se encontro la 
 * palabra en el archivo */

int buscar(char pal[], char archivo[])
{
	int i;
	FILE *fd;
	char pal_archivo[50];
	
	fd = fopen(archivo, "r");
	if (fd == NULL) {
		printf("No se pudo abrir el archivo\n");
		exit(1);
	}

	/* Lee las palabras del archivo y las compara con la palabra a buscar
	* enviada por el padre */
	
	fscanf(fd, "%s", pal_archivo);
	while (!feof(fd)) {
		if (strcmp(pal_archivo, pal) == 0) {
			i++;
		}
		fscanf(fd, "%s", pal_archivo);
	}
	
	fclose(fd);
	return i;
}

/* Funcion que comprueba la validez de los parametros pasados al
 * proceso */

void comprobacion(int argc, char *argv[])
{
	int i;
	
	if (!(argc > 1 && argc < 8)) {
		printf("Numero de argumentos invalidos\n");
		exit(1);
	}

	if(strcmp(argv[1],"-h") == 0) {
		if ((argv[2]) != NULL) {
			printf("-h es excluyente de las otras opciones\n");
			exit(1);
		}
	}else {
		for(i = 1; i < argc; i++) {
			if (strcmp(argv[i],"-d") == 0) {
				if (argv[i+2] == NULL) {
					printf("Falta palabra a buscar\n");
					exit(1);
				}
				if (argv[i+3] == NULL) {
					printf("Falta archivo de salida\n");
				}	
			}
		}
		
		if (strcmp(argv[2],"-n") == 0)
		{
			int num = atoi(argv[3]);
			if (num < 1) {
				printf("n debe ser un entero mayor o igual que 1\n");
				exit(1);
			}
			
			if (argv[4] == NULL) {
				printf("Falta palabra a buscar\n");
			}
			if (argv[5] == NULL) {
				printf("Falta archivo de salida\n");
			}	
		}
	}

}

/* Funcion que comprueba que el archivo a buscar tenga extension .txt
 * Devuelve -1 si el archivo no tiene la extension deseada */

int comptxt(char archivo[]) {
	char tmp[5];
	int i=strlen(archivo);
	
	if (archivo[i-1] == 't') {
		tmp[0] = archivo[i-1];
		tmp[1] = archivo[i-2];
		tmp[2] = archivo[i-3];
		tmp[3] = archivo[i-4];
	} else {
		return -1;
	}	
	
	if (strcmp(tmp, "txt.") != 0) {
			return -1;
	}
}	
