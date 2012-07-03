/********************************************/
/*				 Proyecto 1					*/
/********************************************/
/*			Gustavo Ortega 09-10590			*/
/*		   Katrin Bethencourt 09-10102		*/
/********************************************/

/********************************************/
/*    Archivo principal, que emplea las     */
/*  funciones definidas en proc.h para la 	*/
/*  realización de las diversas actividades	*/
/********************************************/

#include "proc.h"

int main (int argc, char *argv[])
{
	comprobacion(argc, argv);
	
	if(strcmp(argv[1],"-h") == 0) {
		printf(" Sintaxis:\n 	\n pargrep { -h | [-n i] {-f archpalabras | -w palabra} entrada salida }\n");
		printf("\n -h: Imprime esta ayuda.\n -n i: Nivel de concurrencia solicitado, i debe ser mayor o igual que 1.\n");
		printf(" -f archpalabras: Especifica un archivo (archpalabras) con las palabras a buscar   una por línea.\n");
		printf(" -w palabra: Especifica una palabra a ser buscada.\n");
		printf(" -entrada: Archivo de texto de donde serán buscadas las palabras.\n");
		printf(" -salida: Archivo en donde se escribirán las palabras buscadas, y el número de    veces que fueron encontradas\n");
	} else {	
	
		procpadre(argc, argv);
	}	
	
	return 0;
}
