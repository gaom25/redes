	#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/****************************************************************/ 
/* 					FUNCION: comprobacion						*/
/*																*/
/* OBJETIVO: Comprobar la validez de los parametros pasados al	*/
/* proceso.														*/
/*																*/
/* PARAMETROS: Un entero con el numero de argumentos pasados al */
/* proceso, y un apuntador a un arreglo de caracteres que		*/
/* contiene los argumentos pasados al proceso.					*/
/*																*/
/* RETORNO: No retorna nada.								 	*/
/****************************************************************/
void comprobacion(int argc, char *argv[])
{

	if (strcmp(argv[0], "proveedor") == 0) {
		if (argc != 5) {
		printf("Numero de argumentos invalidos\n");
		exit(1);
		}
		
		if (strcmp(argv[2], "-p") == 0) {
			printf("Falta archivo de inventario\n");
			exit(1);
		}
		
		int port = atoi(argv[4]);
		if (port < 2000 || port > 65535) {
			printf("Introduzca un numero de puerto entre 2000-65535\n");
			exit(1);
		}	
	} else {
		if (argc != 6) {
		printf("Numero de argumentos invalidos\n");
		exit(1);
		}
		
		if ((strcmp(argv[1], "-a") != 0) || (strcmp(argv[1], "-b") != 0)) {
			printf("Especifique nivel (-a basico, -b avanzado)\n");
			exit(1);
		}
		
		if (strcmp(argv[3], "-d") == 0) {
			printf("Falta archivo de pedidos\n");
			exit(1);
		}
	}				

}

/****************************************************************/ 
/* 					FUNCION: numlineas							*/
/*																*/
/* OBJETIVO: Contar el numero de lineas que tiene un archivo.	*/
/*																*/
/* PARAMETROS: Ruta del archivo.								*/
/*																*/
/* RETORNO: Entero con el numero de lineas.					 	*/
/****************************************************************/

int numlineas(char arch[])
{
	char archivo[70];
	int n, status;
	FILE *fd;
	
	strcpy(archivo, arch);
	n = 0;
	status = 0;
	
	fd = fopen(archivo, "r");
	if (fd == NULL) {
		printf("No se pudo abrir el archivo %s\n", archivo);
		exit(1);
	}
	
	while ( (status=fgetc(fd)) != EOF ) {
        if (strcmp(status, '\n') == 0)
            n++;
    }
	
	return n;
}		
		
	
	
	
	
	
	
	
	
