#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include "funciones.h"

/* Variables globales */

typedef struct{
		char archivo[125];
		int nomas;
} manejador;
/* El campo "archivo" de esta estructura será empleado para especificar
 * la ruta del archivo donde se buscará la palabra especificada. 
 * El campo "nomas" es un entero que tendrá el valor 1 cuando ya no
 * existan más palabras para buscar */

char palabra[125], salida[125];
int flag;
/* El arreglo "palabra" será empleado para contener la palabra a buscar
 * y el arreglo "salida" contendrá el archivo de salida donde se va a
 * escribir. "flag" es utilizado para saber si se especificó la opción -r */

/****************************************************************/
/*					FUNCION: recursiva							*/
/* OBJETIVO: Hacer la busqueda recursiva de los archivos a 		*/
/* partir del directorio especificado.							*/
/*																*/
/* PARAMETROS: Un arreglo de caracteres con el directorio a		*/
/* partir del cual se buscará, un entero con el número de hilos */
/* y un apuntador a una estructura de tipo manejador			*/
/*																*/
/* RETORNO: No retorna nada.									*/
/* NOTA: Está definida después del main							*/
/****************************************************************/
void recursiva(char dir[], int n, manejador ***d);

/****************************************************************/
/* 					FUNCION: funhilo							*/
/* OBJETIVO: Se ejecutará al crear el hilo. Buscará la palabra	*/
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
	/* temp es un apuntador a una estructura de tipo manejador, que
	 * se utilizará para indicar la palabra a buscar, y si ya no existen
	 * más palabras */
	int j;
	FILE * sld;
	
	/* El hilo se quedará esperando a que el proceso maestro le indique
	 * que ya no quedan más palabras para buscar (cuando el campo "nomas"
	 * tenga un valor distinto de 1) */
	while (1) {
		/* Si el hilo está disponible (si campo de "archivo" es "a")
		 * procede a buscar la palabra especificada en el archivo dado,
		 * a través de la función "buscar" (referirse a funciones.c) */
		if (strcmp(temp->archivo,"a") != 0) {
			j = buscar(palabra,temp->archivo);
			
			/* Escribe en el archivo de salida el archivo que analizó,
			 * la palabra que buscó, y el número de veces que fue
			 * encontrada */			
			sld = fopen(salida,"a");
			if (sld == NULL) {
				printf("No se pudo abrir el archivo\n");
				exit(1);
			}
			fprintf(sld,"%s %s %d\n",temp->archivo, palabra, j);
			fclose(sld);
			
			/* El hilo indica que no está buscando nada */			
			strcpy(temp->archivo, "a");
						
		} else {
			/* Si el hilo no está buscando ninguna palabra, y se le fue
			 * indicado, por el proceso maestro, que ya no hay más
			 * palabras, entonces se sale del ciclo y hace exit */
			if (temp->nomas != 0) {
				break;
			}	
		}
	}
	pthread_exit(NULL);
}

/****************************************/
/* 			FUNCION: main				*/
/****************************************/
void main(int argc, char *argv[]) {
	
	int i, j, k, n, tipo;
	/* "n" es el número de hilos, "tipo" contendrá el tipo del archivo 
	 * que fue leído del directorio */
	
	struct timeval t1, t2;
	long segs, milisegs, microsegs;
	/* t1, t2, segs, milisegs y microsegs son usadas para calcular el 
	 * tiempo de ejecución del programa */
	
	char directorio[100];
	/* "directorio" es un arreglo de caracteres que contiene el directorio 
	 * especificado como parametro en el proceso */
	
	manejador ** datos;
	/* "datos" es un arreglo de estructuras de tipo manejador, inicializado
	 * dinámicamente más adelante */
	
	pthread_t *threads;
	/* "threads" es un arreglo de hilos, inicializado dinámicamente más
	 * adelante */
		
	struct dirent *pDirent;
    DIR *pDir;
    /* pDirent es una estructura para acceder a los campos del
     * directorio, y pDir es un apuntador al stream del directorio */
	
	/* Se comienza a medir el tiempo de ejecución del programa */
	gettimeofday(&t1, NULL);
	
	/* El valor por defecto del número de hilos es 1, y el directorio
	 * es el actual */
	n = 1;
	flag = 0;
	strcpy(directorio,".");
	
	/* Si se especifica la opción -h, se muestra la ayuda, a través de
	 * la función con el mismo nombre (referirse a funciones.c) */
	if (strcmp(argv[1], "-h") == 0) {
		ayuda();
	}
		
	/* Realiza la comprobacion de argumentos */
	comprobacion(argc, argv);
	
	/* Si se especifica la opción -d, se obtiene el directorio donde se 
	 * deben buscar los archivos */
	for (i = 1; i < argc; i++) {
		if (strcmp(argv[i],"-d") == 0) {
			strcpy(directorio, argv[i+1]);
			break;
		}	
	}
		
	/* Si se especifica la opción -n, se obtiene el número de hilos */
	for (i = 1; i < argc; i++) {
		if (strcmp(argv[i],"-n") == 0) {
			n = atoi(argv[i+1]);
			break;
		}
	}
	
	/* Se verifica si se especificó la opción -r */
	for (i = 1; i < argc; i++) {
		if (strcmp(argv[i],"-r") == 0) {
			flag = 1;
			break;
		}
	}
			
	/* Se obtiene la palabra a buscar y el archivo de salida */
	strcpy(palabra, argv[argc-2]);
	strcpy(salida, argv[argc-1]);
	
	/* Se inicializa el arreglo de estructuras de tipo manejador, 
	 * comprobando si se produjo un error al alocar memoria */
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
	
	/* Se inicializa el arreglo de hilos de tipo manejador, 
	 * comprobando si se produjo un error al alocar memoria */
	threads = (pthread_t *) malloc(n * sizeof(pthread_t));
	if (threads == NULL) {
		printf("Error al alocar memoria, intente mas tarde\n");
		exit(1);
	}	

	/* Se crean todos los hilos primero y se quedan esperando archivos */
	for(i = 0; i < n; i++) {
		/* Se le dice que no esta trabajando ningun archivo, y que
		 * todavia quedan palabras por buscar, para que espere */
		strcpy(datos[i]->archivo,"a");
		datos[i]->nomas = 0;
		k = pthread_create(&threads[i], NULL, funhilo, datos[i]);
		if (k) {
			printf("Se produjo un error al crear el hilo: %d\n", k);	
		}
	}	

	/* Escritura por pantalla  */
	
	printf("Directorio: %s\n", directorio);
	printf("Palabra: %s\n", palabra);
	printf("Numero de hilos: %d\n", n);


	/* Se llama a la función "recursiva" para buscar recursivamente los
	 * archivos en los directorios */
	recursiva(directorio,n,&datos);
	
	/* Una vez que termine,el hilo maestro le indica a cada hilo
	 * que no quedan más palabras por buscar, y se queda esperando por
	 * su terminación */
	for(i = 0; i < n; i++) {
		datos[i]->nomas = 1;
		pthread_join(threads[i],NULL);
	}
	
	for(i = 0; i < n; i++){
		free(datos[i]);
	}
	free(datos);
	free(threads);
	
	
	gettimeofday(&t2, NULL);
	
	/* Cálculo del tiempo de ejecución del programa en milisegundos */
	segs = t2.tv_sec - t1.tv_sec;
	microsegs = t2.tv_usec - t1.tv_usec;
	milisegs = ((segs) * 1000 + microsegs/1000.0) + 0.5;
	printf("Tiempo total de busqueda: %ld milisegundos\n",milisegs);
	
					
}

void recursiva(char dir[], int n, manejador ***d) {
	manejador **datos;
	/* Estructura de tipo manejador, cuyo campo "archivo" será 
	 * utilizado para indicarle al hilo la palabra que debe buscar */	
	
	char ruta[125], dirtmp[125];
	/* El arreglo "dirtmp" será utilizado para indicarle al hilo la ruta
	 * del archivo donde debe buscar la palabra (si es un archivo regular),
	 * el arreglo "ruta" será empleado para concatenar los directorios
	 * recursivamente */
	
	int i, j, tipo;
	/* "tipo" contendrá el tipo del archivo que fue leído del directorio */
	
	struct dirent *pDirent;
	DIR *pDir;
	 /* pDirent es una estructura para acceder a los campos del
     * directorio, y pDir es un apuntador al stream del directorio */
     
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
		
		/* Si es un archivo regular, se le pasa directamente al hilo */
		if (tipo == 8) {
			/* Se comprueba que el archivo del directorio sea de 
			 * extension .txt */
			j = comptxt(pDirent->d_name);
			/* Si no es .txt lo ignora y pasa a buscar otro archivo */		
			if (j == -1) {
				continue;					
			} else {
				/* Concatena el archivo que se encontró en el directorio
				 * que está siendo leído, con la ruta del directorio, 
				 * para formar la ruta completa del archivo donde se 
				 * debe buscar la palabra */
				strcpy(dirtmp, dir);
				if (strcmp(dirtmp, ".") == 0) {
					strcpy(dirtmp, "./");
					strcat(dirtmp, pDirent->d_name);
				} else {
					strcat(dirtmp, pDirent->d_name);
				}		
				
				/* Se queda esperando por algún hilo que no esté
				 * trabajando en un archivo */
				while (strcmp(datos[i]->archivo, "a") != 0) {
					i = (i+1)%n;
				}
				strcpy(datos[i]->archivo, dirtmp);
				printf("%s\n", datos[i]->archivo);
			}	
		}
		
		/* Si es un directorio, verifica que no sea ni el directorio
		 * padre, ni el actual, y concatena el directorio anterior con el
		 * nuevo, para formar la nueva ruta*/
		if ((tipo == 4) && (flag == 1)) {
			if (strcmp (pDirent->d_name, "..") != 0 && strcmp (pDirent -> d_name, ".") != 0) {
				snprintf (ruta, 125,"%s%s/", dir, pDirent->d_name);
				/* Llama recursivamente a la función con la nueva ruta*/
				recursiva(ruta,n,&datos);
			}
		}
	}	
}		
 
