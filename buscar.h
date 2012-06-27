#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int buscar(char pal[], char archivo[])
{
	FILE *fd;
	char pal_archivo[50], tmp[5];
	int i=strlen(archivo);
	
	if (archivo[i] == 't') {
		tmp[0] = archivo[i];
		tmp[1] = archivo[i-1];
		tmp[2] = archivo[i-2];
		tmp[3] = archivo[i-3];
		
		if (strcmp(tmp, "txt.") != 0) {
			return -1;
		}	
	}
	
	i = 0;
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

void comprobacion(int argc, char *argv[])
{
	int i;
	
	if (!(argc > 1 && argc < 9)) {
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
		if (strcmp(argv[2],"-n") == 0)
		{
			int num = atoi(argv[2]);
			if (num < 1) {
				printf("n debe ser un entero mayor o igual que 1\n");
				exit(1);
			}
		}
	}

}
