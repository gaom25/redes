#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int buscar(char pal[], char palabras[])
{
	FILE *fd;
	char pal_archivo[50];
	int i=0,j=-1;

	if (strcmp(pal, "NOMAS") == 0) {
		return j;
	}
	
	for(i = strlen(palabras); i>-1;i--){
		if(palabras[i] == '.'){
			break;
		}
	}
	if(i == -1){
		printf("archivo no valido\n");
		return -1;
	}else{
		i = 0;
		fd = fopen(palabras, "r");
		if (fd == NULL) {
			printf("No se pudo abrir el archivo\n");
			exit(1);
		}

		/* Lee las palabras del archivo y las compara con la palabra a buscar
		* enviada por el padre */
		fscanf(fd, "%s", pal_archivo);
		while(!feof(fd)) {
			if (strcmp(pal_archivo, pal) == 0) {
				i++;
			}
			fscanf(fd, "%s", pal_archivo);
		}
		
		fclose(fd);
		return i;
	}
}
