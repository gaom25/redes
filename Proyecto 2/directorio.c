#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include "buscar.h"

int main(int argc, char *argv[]){
    
    char tmp[80], directorio[100], palabra[50], salida[50], archivo[150];
    int len, tipo, count, guardia, i, j;
    struct dirent *pDirent;
    DIR *pDir;
    guardia = 0;
   
   /* Aqui vendria la comprobacion de argumentos */
   
   /* Si se especifica la opcion -d, se obtiene el directorio, por
    * default es '.' */
   
	for (i = 1; i < argc; i++) {
		if (strcmp(argv[i],"-d") == 0) {
			strcpy(directorio, argv[i+1]);
			guardia = 1;
		}
	}
	if (guardia != 0) {
		strcmp(directorio, ".");
	}
	
	/* Se obtiene la palabra a buscar y el archivo de salida */
	
	strcpy(palabra, argv[argc-2]);
	strcpy(salida, argv[argc-1]); 
	
	/* El proceso maestro busca los archivos .txt en el directorio
	 * especificado */	
	
    pDir = opendir(directorio);
    if (pDir == NULL) {
        printf("No se puede abrir el directorio '%s'\n", directorio);
        exit(1);
    }

	printf("palabra: %s \n", palabra);
    while ((pDirent = readdir(pDir)) != NULL) {
        printf("[%s]\n", pDirent->d_name);
        tipo = pDirent->d_type;
        
        if (tipo == 8) {
			strcpy(archivo, argv[1]);
			strcat(archivo, pDirent->d_name);
			j = strlen(archivo);
			
			if (archivo[j] == 't') {
				tmp[0] = archivo[j];
				tmp[1] = archivo[j-1];
				tmp[2] = archivo[j-2];
				tmp[3] = archivo[j-3];
		
				if (strcmp(tmp, "txt.") != 0) {
					continue;
					/* Que si no es .txt lo ignore y pase a buscar
					 * otro archivo */
				} else {
					/* Si termina en .txt pone al hilo a buscar la
					 * palabra...el peo es que si nos especifican el
					 * numero de hilos, solo se deben crear n hilos,
					 * no se como poner eso */
				}	 
			}
		}			
	}
			
			
		  
    closedir (pDir);
    return 0;
}
