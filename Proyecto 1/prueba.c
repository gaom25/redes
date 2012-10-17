#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	char nombre[20];
	char hostname[50];
	char producto[30];
	int numport;
	int cantidad;
	int precio;
} proveedor;

int main() {
	
	FILE *fd;
	char *pal_archivo = NULL;
	int i = 0;
	int num = 3;
	size_t len;
	size_t read;
	proveedor ** datos;
	int count = 0;
	
	datos = (proveedor **) malloc(num * sizeof(proveedor *));
	if (datos == NULL) {
		printf("Error al alocar memoria, intente mas tarde\n");
		exit(1);
	}	
	for(i = 0; i < num; i++){
			datos[i] = (proveedor *) malloc(sizeof(proveedor));
			if (datos[i] == NULL) {
				printf("Error al alocar memoria, intente mas tarde\n");
				exit(1);
			}	
	}
	
	i = 0;
		
	fd = fopen("prueba.txt", "r");
	if (fd == NULL) {
		printf("No se pudo abrir el archivo\n");
		exit(1);
	}

			
	while((read = getdelim(&pal_archivo,&len,'&',fd))!= -1)
	{
		if (pal_archivo == "\n") {
			i++;
			count = 0;
			printf("Llegue aqui");
		}
		
		if (count == 0) {
			if (pal_archivo[strlen(pal_archivo)-1] == '&')
				pal_archivo[strlen(pal_archivo)-1] = '\0';
			
			strcpy(datos[i]->nombre, pal_archivo);
			printf("Nombre del proveedor: %s\n", datos[i]->nombre);
			printf("Estoy en proveedor %d\n", i);
		}
		
		if (count == 1) {
			if (pal_archivo[strlen(pal_archivo)-1] == '&')
				pal_archivo[strlen(pal_archivo)-1] = '\0';
			
			if (pal_archivo[strlen(pal_archivo)-1] == ' ')
				pal_archivo[strlen(pal_archivo)-1] = '\0';
			
			/*if (pal_archivo[strlen(pal_archivo)-1] == '\n')
				pal_archivo[strlen(pal_archivo)-1] = '\0';*/
				
			memmove(pal_archivo, pal_archivo+1, strlen(pal_archivo));		
			
			strcpy(datos[i]->hostname, pal_archivo);
			printf("Hostname: %s\n",datos[i]->hostname);
			printf("Estoy en proveedor %d\n", i);
		}
		if (count == 2) {
			if (pal_archivo[strlen(pal_archivo)-1] == '&')
				pal_archivo[strlen(pal_archivo)-1] = '\0';
			
			if (pal_archivo[strlen(pal_archivo)-1] == ' ')
				pal_archivo[strlen(pal_archivo)-1] = '\0';
			
			/*if (pal_archivo[strlen(pal_archivo)-1] == '\n')
				pal_archivo[strlen(pal_archivo)-1] = '\0';*/
				
			memmove(pal_archivo, pal_archivo+1, strlen(pal_archivo));
			
			datos[i]->numport = atoi(pal_archivo);
			printf("Puerto: %d\n",datos[i]->numport);
			printf("Estoy en proveedor %d\n", i);
		}			
		
		/*if (pal_archivo[strlen(pal_archivo)-1] == '&')
			pal_archivo[strlen(pal_archivo)-1] = '\0';
			
		if (pal_archivo[strlen(pal_archivo)-1] == ' ')
			pal_archivo[strlen(pal_archivo)-1] = '\0';
			
		if (pal_archivo[strlen(pal_archivo)-1] == '\n')
			pal_archivo[strlen(pal_archivo)-1] = '\0';
			
		memmove(pal_archivo, pal_archivo+1, strlen(pal_archivo)); */
		
		count++;
	}
	
	free(pal_archivo);
	fclose(fd);		
	
	return 0;
}			
			
