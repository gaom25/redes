#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include "funciones.c"

/* Variables globales */
typedef struct{
		char archivo[100];
		int nomas;
} manejador;

void recursiva(char dir[], int n, manejador ***d);

char palabra[100], salida[50];

/****************************************************************/
/* 					FUNCION: funhilo							*/
/* OBJETIVO: Se ejecutara al crear el hilo. Buscara la palabra	*/
/* especificada en el archivo pasado por el proceso maestro.	*/
/* 																*/
/* PARAMETROS: Una estructura de tipo manejador.				*/
/* 																*/
/* VARIABLES GLOBALES: Estructura "manejador" y arreglo de		*/ 
/* caracteres "palabra".										*/
/****************************************************************/
void *funhilo(void *datos)
{	
	manejador *temp;
	temp = datos;
	int j;
	
	while (1) {
		if (strcmp(temp->archivo,"a") != 0) {
			printf("asdasd: %s\n", temp->archivo);
			j = buscar(palabra,temp->archivo);
						
			FILE * sld = fopen(salida,"a");
			if (sld == NULL) {
				printf("No se pudo abrir el archivo\n");
				exit(1);
			}
			fprintf(sld,"%s %s %d\n",temp->archivo, palabra, j);
			fclose(sld);
						
			strcpy(temp->archivo, "a");
						
		} else {
			if (temp->nomas != 0) {
				break;
			}	
		}
	}
	pthread_exit(NULL);
}


void main(int argc, char *argv[]) {
	
	struct timeval tempo1, tempo2;
	long elapsed_seconds;
	long elapsed_mtime;
	long elapsed_useconds;
	gettimeofday(&tempo1, NULL);
	char directorio[100];
	/* "directorio" es un arreglo de caracteres que contiene el directorio 
	 * especificado como parametro en el proceso */
	manejador ** datos;
	pthread_t *threads;
	
	int i, j, k, n, tipo;
	/* "tipo" es un entero que contendra el tipo de archivo recorrido */
	struct dirent *pDirent;
    DIR *pDir;
	
	n = 1;
	
	if (strcmp(argv[1], "-h") == 0) {
		ayuda();
	}
		
	/* Realiza la comprobacion de argumentos */
	comprobacion(argc, argv);
	
	/* Obtiene el directorio donde se debe buscar */
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
	
	datos = (manejador **) malloc(n * sizeof(manejador *));
	if (datos == NULL) {
		printf("Error al alocar memoria, intente mas tarde\n");
		exit(1);
	}	
	for(i = 0; i < n; i++){
			datos[i] = (manejador *) malloc(sizeof(manejador));
			if (datos[i] == NULL) {
				printf("Error al alocar memoria, intente mas tarde\n");
				exit(1);
			}	
	}	
	
	threads = (pthread_t *) malloc(n * sizeof(pthread_t));
	if (threads == NULL) {
		printf("Error al alocar memoria, intente mas tarde\n");
		exit(1);
	}	
			
	/* Obtiene la palabra a buscar y el archivo de salida */
	strcpy(palabra, argv[argc-2]);
	strcpy(salida, argv[argc-1]);
	
	

	/* Se crean todos los hilos primero y se quedan esperando archivos */
	for(i = 0; i < n; i++) {
		strcpy(datos[i]->archivo,"a");
		datos[i]->nomas = 0;
		k = pthread_create(&threads[i], NULL, funhilo, datos[i]);
		if (k) {
			printf("Se produjo un error al crear el hilo: %d\n", k);	
		}
	}	

	recursiva(directorio,n,&datos);
	
	for(i = 0; i < n; i++) {
		datos[i]->nomas = 1;
		pthread_join(threads[i],NULL);
	}
	
	
	gettimeofday(&tempo2, NULL);
	
	/* IMPRESIONES */
	
	printf("Directorio: %s\n", directorio);
	printf("Palabra: %s\n", palabra);
	printf("Numero de hilos: %d\n", n);
	
	elapsed_seconds  = tempo2.tv_sec  - tempo1.tv_sec;
	elapsed_useconds = tempo2.tv_usec - tempo1.tv_usec;
	elapsed_mtime = ((elapsed_seconds) * 1000 + elapsed_useconds/1000.0) + 0.5;
	printf("Tiempo total de busqueda en milisegundos %ld\n",elapsed_mtime);
	
					
}

void recursiva(char dir[], int n, manejador ***d) {
	manejador **datos;	
	char ruta[100], dirtmp[100];
	int i, j, tipo;
	struct dirent *pDirent;
	DIR *pDir;
	datos = *d;
	i = 0;
	
	/* Se abre el directorio especificado, y se indica si se produjo 
	 * un error */
	pDir = opendir(dir);
    if (pDir == NULL) {
        printf("No se puede abrir el directorio '%s'\n", dir);
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
				strcpy(dirtmp, dir);
				
				strcat(dirtmp, pDirent->d_name);
				
				while (strcmp(datos[i]->archivo, "a") != 0) {
					i = (i+1)%n;
				}
				strcpy(datos[i]->archivo, dirtmp);
				printf("%s\n", datos[i]->archivo);
			}	
		}
		
		if (tipo == 4) {
			if (strcmp (pDirent->d_name, "..") != 0 && strcmp (pDirent -> d_name, ".") != 0) {
				snprintf (ruta, 100,"%s%s/", dir, pDirent->d_name);
				//printf ("%s\n", ruta);
				/* Llama recursivamente a la funcion con la nueva ruta*/
				recursiva(ruta,n,&datos);
			}
		}
	}	
}		
 
