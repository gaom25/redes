/********************************************/
/*				 Proyecto 1					*/
/********************************************/
/*			Gustavo Ortega 09-10590			*/
/*		   Katrin Bethencourt 09-10102		*/
/********************************************/

/********************************************/
/*  Header que contiene los procedimientos  */
/* 			 usados en el main			    */
/********************************************/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "lista.h"
#include "listap.h"

void procpadre(int argc, char *argv[]);
void comprobacion(int argc, char *argv[]);
int prochijo(int argc, char *argv[], char palabras[]);

/* Función que comprueba el pase de argumentos */
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

/* Función del proceso padre */
void procpadre(int argc, char *argv[])
{
	FILE *fd;
	Lista *cb = NULL;
	Listap *pal = NULL;
	int **ph, **pp;
	char palabras[50], titulo[50], salida[50], pal_buscar[50],num_veces[50], pal_hijo[50];
	int i, j, k, n, hpid, num, guardia, pidh, pidp, p1, p2;
	guardia = 0;
	j = 0; 
	k = 0; 
	num = 0;

	/* Si se especifica la opción -f, se obtiene el nombre del archivo
	* de donde se deben extraer las palabras y se guarda en titulo[] */
	for (i = 1; i < argc; i++) {
		if (strcmp(argv[i],"-f") == 0) {
			strcpy(titulo, argv[i+1]);
		}
	}

	/* Si se especifica la opcion -w, se obtiene la palabra a buscar */
	for (i = 1; i < argc; i++) {
		if (strcmp(argv[i],"-w") == 0) {
			strcpy(pal_buscar, argv[i+1]);
			guardia=1;
		}
	}

	/* Obtiene el numero de procesos concurrentes */
	for (i = 1; i < argc; i++) {
		if (strcmp(argv[i],"-n") == 0) {
			n = atoi(argv[i+1]);
			break;
		} else {
			n = 1;
		}
	}

	/* Guarda en el arreglo salida[] el nombre del archivo de salida */
	strcpy(salida, argv[argc-1]);
	
	/* Si se especifica la opción -f */
	if (guardia != 1) {
		/* Abre el archivo de palabras a buscar */
		fd = fopen(titulo, "r");
		if (fd == NULL) {
			printf("No se pudo abrir el archivo\n");
			exit(1);
		}

		/* Se comienza a leer las palabras y se guardan en una
		* estructura */
		fscanf(fd, "%s", pal_buscar);
		while(!feof(fd)) {
			insertar(pal_buscar,&cb);
			fscanf(fd, "%s", pal_buscar);
		}
		fclose(fd);
	}

	/* Crea la matriz de pipes */
	ph = (int **)malloc(n * sizeof(int *));  
	for(i = 0 ; i < n ; i++) {
		ph[i] = (int *)malloc (2 * sizeof(int));
	}
    
	pp = (int **)malloc(n * sizeof(int *)); 
	for (i = 0 ; i < n ; i++) {
		pp[i] = (int *)malloc (2 * sizeof(int));
	}	

	/* Crea los pipes para la comunicación entre padre e hijos */
	for(i = 0; i< n; i++) {
		p1 = pipe(ph[i]);
		p2 = pipe(pp[i]);
		if ( p1 == -1 && p2 == -1)
		{
			printf("Error al crear el pipe\n");
			exit(1);
		}	
	}

	/* Se crean los n procesos hijos */
	for(j=0; j<n; j++) {
		hpid=fork();
		if (hpid < 0) {
			printf("Error al crear el proceso hijo\n");
			exit(1);
		}else if(hpid == 0){
			break;
		}
		
	}

	/* Si es el proceso padre */
	if (hpid != 0) {
		/* Si la opción -f fue especificada, escribe en el pipe la
		 * palabra que obtiene de la estructura */ 
		
		if (guardia != 1) {
			for (i=0; i<n; i++) {
				agrpal(&cb,ph,i);
			}		
		
		/* Si se especificó la opcion -w, le pasa la palabra al proceso
		 * hijo, y si el usuario pidió más procesos, se les dice a los 
		 * otros que ya no hay mas palabras */		
		} else {
			write(ph[0][1],pal_buscar,strlen(pal_buscar)+1);
			for(i=1; i<n; i++) {
				write(ph[i][1],"NOMAS",6);
			}	
		}
		
		/* Ciclo que ejecuta el padre, leyendo por los pipes las palabras
		 * y el número de veces que fueron encontradas por cada hijo, 
		 * y escribe en el archivo de salida */
		while (k != n) {	
			for(i=0; i<n && k != n; i++) {	
				read(pp[i][0], num_veces, 50);
				read(pp[i][0], pal_hijo, 50);
			
				int occur = atoi(num_veces);
			
				/* Si el número escrito en el pipe por el hijo es -1, 
				 * significa que hizo exit */
				if (occur != -1) {
					FILE * sld = fopen(salida,"a");
					if (sld == NULL) {
						printf("No se pudo abrir el archivo\n");
						exit(1);
					}
					fprintf(sld,"La cantidad de ocurrencias de la palabra %s es : %d\n",pal_hijo,occur);
					fclose(sld);

					agrpal(&cb,ph,i);
			
				} else {
					k++;
				}
			}
		}
		
		liberarp(&pal);
		liberar(&cb);
		free(ph);
		free(pp);

		exit(0);

	/* Si es el proceso hijo */
	} else {
		/* Mientras el padre no le haya indicado al hijo que ya no hay 
		 * más palabras para enviar, lee la palabra que le paso el padre
		 * y la guarda en una estructura, luego procede a buscarla, y
		 * por último le envia al padre la palabra que buscó y el número
		 * de veces que la encontró */
		while(num != -1) {
			read(ph[j][0], palabras, 50);
			insertarp(palabras,getpid(),&pal);

			num = prochijo(argc, argv, palabras);
			sprintf(num_veces,"%d",num);

			write(pp[j][1], num_veces, 50);
			write(pp[j][1], palabras, 50);
		}
		
		/* Cuando haya finalizado, cierra su respectivo pipe */
		
		close(pp[j][0]);
		close(ph[j][1]);
		close(ph[j][0]);
				
		/* Imprime su PID, el PID de su padre y las palabras que busco */
		pidh = getpid();
		pidp = getppid();
		sleep(0.1);
		printf("Mi PID es %d, el PID de mi padre es %d y las palabras que encontre fueron:\n", pidh, pidp);
		busprt(&pal,pidh);
		
		exit(0);
	}
}	

/* Función del proceso hijo */
int prochijo(int argc, char *argv[], char palabras[])
{
	FILE *fd;
	char entrada[50], pal_archivo[50];
	int i=0,j=-1;

	if (strcmp(palabras, "NOMAS") == 0) {
		return j;
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
	fscanf(fd, "%s", pal_archivo);
	while(!feof(fd)) {
		if (strcmp(pal_archivo, palabras) == 0) {
			i++;
		}
		fscanf(fd, "%s", pal_archivo);
	}
	
	fclose(fd);
	return i;
}
