/*falta hacer que el padre sepa cual palabra le paso a cada uno de sus hijos, que los hijos sepan cuales palabras les han 
pasado, el pipe esta bien, y las pruebas*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "lista.h"

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
	cb = NULL;
	char palabras[50], titulo[50], pal_buscar[50],num_veces[50];
	int i, n, hpid, num,status,pid_hijo;
		
	/* Nombre del archivo que contiene las palabras queda en titulo[]*/
	for (i = 1; i < argc; i++) {
		if (strcmp(argv[i],"-f") == 0) {
			strcpy(titulo, argv[i+1]);
		}
	}
	
	/* Numero de procesos concurrentes */
	for (i = 1; i < argc; i++) {	
		if (strcmp(argv[i],"-n") == 0) {
			n = atoi(argv[i+1]);
		} else {
			n = 1;
		}	
	}	

	/* Abre el archivo de palabras a buscar*/
	fd = fopen(titulo, "r");
	if (fd == NULL) {
		printf("No se pudo abrir el archivo\n");
		exit(1);
	}
			
	
	/* El proceso padre comienza a leer las palabras y las guarda en 
	 * una estructura */
	
	fscanf(fd, "%s", pal_buscar);
	while(!feof(fd)) {
		insertar(pal_buscar,&cb);
		fscanf(fd, "%s", pal_buscar);
	}
	
	/* Crea los pipes para la comunicacion entre padre e hijos */
	
	int ph[n][2];  
	int pp[n][2];
	
	/*arreglo que determina que palabra fue pasada al proceso hijo, aun por trabajar*/
	
	char *procesos[n][2];
	for(i = 0; i< n; i++) {
		pipe(ph[i]);
		pipe(pp[i]);
		
	}		
	
	/* Accede a la estructura para buscar las palabras */
	for(i=0; i<n; i++) {
		hpid=fork();
		if (hpid < 0) {
			printf("Error al crear el proceso hijo\n");
			exit(1);
		}
			
		if (hpid != 0) {	// Si es el proceso padre
			agrpal(&cb,&ph,i);
			//escribir(argc, argv, num_veces);
		} else {		// Si es el proceso hijo
			num = 0;
			while(num != -1) {				
				close(ph[i][1]);
				read(ph[i][0], palabras, 50);
				close(ph[i][0]);
			
				while(palabras == NULL) {
					close(ph[i][1]);
					read(ph[i][0], palabras, 50);
					close(ph[i][0]);
				}
				num = prochijo(argc, argv, palabras);
				
				if(num != -1) {				
					sprintf(num_veces,"%d",num);
				
					close(pp[i][1]);
					write(pp[i][0], num_veces, sizeof(num_veces)+1);
					close(pp[i][0]);
				}
			}
		exit(0);
		}			
	}
		
		while((pid_hijo = wait(&status)) != -1){
			/* buscar nueva palabra y pasarsela al hijo con ese pid_hijo, tambien revisar y
			el exit del hijo fue exitoso y ver el numero de palabras que trajo*/
			close(pp[i][1]);
			read(pp[i][0], num_veces, 50);
			close(pp[i][0]);
			char c[] = "hola";
			
			int occur = atoi(num_veces);
			
			FILE * sld = fopen("salida.txt","a");
			if(sld ==NULL) {
				printf("nose pudo abrir el archivo\n");
				break;	
			}
			fprintf(sld,"La cantidad de ocurrencias de la palabra %s es : %d\n",c,occur);
			fclose(sld);
					
			agrpal(&cb,&ph,i);
			
		}		
}		

/* Funcion del proceso hijo */

int prochijo(int argc, char *argv[], char palabras[])
{
	FILE *fd;
	char entrada[50], pal_archivo[50];
	int i=0,j, pidh, pidp;
	j = -1;
	printf("%s\n",palabras);
	
	if (strcmp(palabras, "NOMAS") == 0) {
		pidh = getpid();
		pidp = getppid();
		printf("Mi PID es %d, el PID de mi padre es %d", pidh, pidp);
		// FALTARIA IMPRIMIR TODAS LAS PALABRAS QUE BUSCO
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
	while(!feof(fd)) {
		fscanf(fd, "%s", pal_archivo);
		if (strcmp(pal_archivo, palabras) == 0) {
			i++;
		}
	}	
	
	return i;
}
