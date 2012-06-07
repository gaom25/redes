/*falta hacer que el padre sepa cual palabra le paso a cada uno de sus hijos, que los hijos sepan cuales palabras les han
pasado, el pipe esta bien, y las pruebas*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "lista.h"
#include "listap.h"

void procpadre(int argc, char *argv[]);
void titulo_pal(int argc, char *argv[]);
void comprobacion(int argc, char *argv[]);
int prochijo(int argc, char *argv[], char palabras[]);

int main (int argc, char *argv[])
{

comprobacion(argc, argv);
procpadre(argc, argv);

/*printf("args: %d \n", argc);
printf("array[0]: %s \n", argv[0]);
printf("array[1]: %s \n", argv[1]);
printf("array[2]: %s \n", argv[2]);
printf("arch entrada: %s \n", argv[argc-2]);*/

}

/* Funcion que comprueba el pase de argumentos */
void comprobacion(int argc, char *argv[])
{
	if (!(argc > 1 && argc < 9)) {
		printf("Numero de argumentos invalidos\n");
		exit(1);
	}

	if(strcmp(argv[1],"-h") == 0) {
		if ((argv[2]) != NULL) {
		printf("-h es excluyente de las otras opciones\n");
		exit(1);
		}
	}else{

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

/* Funcion del proceso padre */
void procpadre(int argc, char *argv[])
{
	FILE *fd;
	Lista *cb;
	Listap *pal;
	cb = NULL;
	pal = NULL;
	int   **ph, **pp;
	char palabras[50], titulo[50], pal_buscar[50],num_veces[50], c[50];
	int i, j, k, n, hpid, num,status,pid_hijo, guardia,pidh, pidp;
	guardia=0;
	j=0;
	k=0;

	/* Si se especifica la opcion -f, se obtiene el nombre del archivo
	* de donde se deben extraer las palabras */
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

	/* Numero de procesos concurrentes */
	for (i = 1; i < argc; i++) {
		if (strcmp(argv[i],"-n") == 0) {
			n = atoi(argv[i+1]);
			break;
		} else {
			n = 1;
		}
	}

	/* Si se especifica la opcion -f */
	if (guardia != 1) {
	/* Abre el archivo de palabras a buscar*/
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

	/* Crea los pipes para la comunicacion entre padre e hijos */
	for(i = 0; i< n; i++) {
		pipe(ph[i]);
		pipe(pp[i]);
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

	if (hpid != 0) { // Si es el proceso padre
		if (guardia != 1) {
			for (i=0; i<n; i++) {
				agrpal(&cb,ph,i);
			}	
		} else {
			write(ph[0][1],pal_buscar,strlen(pal_buscar)+1);
			for(i=1; i<n; i++) {
				write(ph[i][1],"NOMAS",6);
			}	
		}
		
		while (k != n) {	
			for(i=0; i<n && k != n; i++) {	
				read(pp[i][0], num_veces, 50);
				read(pp[i][0], c, 50);
			
				int occur = atoi(num_veces);
			
				if (occur != -1) {
					FILE * sld = fopen("salida.txt","a");
					if (sld == NULL) {
						printf("No se pudo abrir el archivo\n");
						break;
					}
					fprintf(sld,"La cantidad de ocurrencias de la palabra %s es : %d\n",c,occur);
					fclose(sld);

					agrpal(&cb,ph,i);
			
				} else {
					k++;
				}
			}
		}
		
		/* Espera a que todos los hijos hayan finalizado, cierra los 
		 * pipes y libera memoria */
		
		//liberarp(&pal);
		//liberar(&cb);

		exit(0);

	} else { // Si es el proceso hijo
		num = 0;
		while(num != -1) {
			
			read(ph[j][0], palabras, 50);
			//if(strcpy(palabras,"NOMAS") != 0){
				insertarp(palabras,getpid(),&pal);
			//}
			num = prochijo(argc, argv, palabras);

			sprintf(num_veces,"%d",num);

			write(pp[j][1], num_veces, 50);
			write(pp[j][1], palabras, 50);
			
		}
		
		
		close(pp[j][0]);
		close(ph[j][1]);
		close(ph[j][0]);
		//imprimirp(&pal);	
		pidh = getpid();
		pidp = getppid();
		sleep(0.1);
		printf("Mi PID es %d, el PID de mi padre es %d y las palabras que encontre fueron:\n", pidh, pidp);
		busprt(&pal,pidh);
		exit(0);
	}
}	



/* El padre recibe del hijo el numero de veces que encontro la palabra
* y busca la nueva palabra para pasarsela al hijo, revisando si el exit
* del hijo fue existoso */


/* Funcion del proceso hijo */

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

	return i;
}
