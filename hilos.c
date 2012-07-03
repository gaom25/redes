#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "funciones.c"

typedef struct{
		char archivo[120];
		int nomas;
} manejador;

char palabra[50], salida[50];

/* Funcion que llevara a cabo el hilo */
void *funhilo(void *datos)
{	
	manejador *temp = datos;
	int j;
		
	//while (1) {
		if (temp->archivo != NULL) {
			j = buscar(palabra,temp->archivo);
			printf("Numero de veces que sale %s es %d\n", palabra, j);
			
			temp->archivo == NULL;
			
		} else {
			if (temp->nomas != 0) {
				//break;
			}	
		}
	//}		
}


void main(int argc, char *argv[]){
	
	char directorio[120];
	int i, j, k, n, tipo;
	manejador datos[n];
	pthread_t threads[n];
	struct dirent *pDirent;
    DIR *pDir;
	
	n = 1;
	
	/* Realiza la comprobacion de argumentos */
	comprobacion(argc, argv);
	
	/* Obtiene el directorio donde se debe buscar y lo guarda en la
	 * variable directorio */
	for (i = 1; i < argc; i++) {
		if (strcmp(argv[i],"-d") == 0) {
			strcpy(directorio, argv[i+1]);
			break;
		}
	}
	
	/* Obtiene el numero de hilos a usar */
	for (i = 1; i < argc; i++) {
		if (strcmp(argv[i],"-n") == 0) {
			n = atoi(argv[i+1]);
			break;
		}
	}
	
	/* Obtiene la palabra a buscar y el archivo de salida */
	strcpy(palabra, argv[argc-2]);
	strcpy(salida, argv[argc-1]);
	
	/* Se abre el directorio especificado, y se indica si se produjo 
	 * un error */
	pDir = opendir(directorio);
    if (pDir == NULL) {
        printf("No se puede abrir el directorio '%s'\n", directorio);
        exit(1);
    }

	/* Comienza a leer el directorio */
    while ((pDirent = readdir(pDir)) != NULL) {
        tipo = pDirent->d_type;
        
        if (tipo == 8) {
			/* Se comprueba que el archivo del directorio sea de 
			 * extension .txt */
			j = comptxt(pDirent->d_name);
			
			/* Si no es .txt lo ignora y pasa a buscar otro archivo */		
			if (j == -1) {
				continue;
			} else {
				/* Concatena el archivo que se encontro en el directorio
				 * que esta haciendo leido, con la ruta del directorio, 
				 * para formar la ruta completa del archivo donde se 
				 * debe buscar la palabra */
				
				strcat(directorio, pDirent->d_name);
				printf("ruta completa: %s\n", directorio);
				
				/* Se ponen a los hilos a buscar las palabras */
				for(i = 0; i < n; i++) {
					strcpy(datos[i].archivo, directorio);
					k = pthread_create(&threads[i], NULL, funhilo, &datos[i]);
					if (k) {
						printf("Se produjo un error al crear el hilo: %d\n", k);	
					}
				}
								
				for(i = 0; i < n; i++) {
					pthread_join(threads[i], NULL);
				}	
					
			}	 
		}
	}
					
}
	
	
	
	/* while(datos[i].sali != 1){
			i = (i+1)%y;
	}
	
	for(i = 0; i<y;i++){
		strcpy(datos[i].archivo,chao);
	}
	for(i = 0;i<y;i++){
		datos[i].esta = 0;
		pthread_join(threads[i],NULL);
	}
	pthread_exit(NULL); */
	
 
