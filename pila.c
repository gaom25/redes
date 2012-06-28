/********************************************/
/*				 Proyecto 1					*/
/********************************************/
/*			Gustavo Ortega 09-10590			*/
/*		   Katrin Bethencourt 09-10102		*/
/********************************************/

/********************************************/
/*    Header que crea la lista utilizada    */
/*    para guardar las palabras a buscar	*/
/********************************************/

#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

/* Definición de la Pila */
 struct est {									
 	char nombre[51];
 	struct est *proximo;
 };
   
typedef struct est Pila;

/* Procedimiento para insertar una nueva palabra en la Pila */
void empilar(char palabras[], Pila **L)				
{
	Pila *new;
	Pila *prox = *L;
	   
	new = (Pila *)malloc(sizeof (Pila));
	   
	if (new == NULL) {
		printf("Memoria llena\n");
	} else {
		strcpy(new->nombre, palabras);
		new->proximo = NULL;
		 
	    if (prox == NULL) {
			*L = new; 
		} else {
			new->proximo = prox;
			*L = new;
	       
		}
	}
}
			

void desempilar(char palabra[],Pila **cabeza){
		Pila *rm;
		rm = *cabeza;
		*cabeza = rm->proximo;
		strcpy(palabra,rm->nombre);
		free(rm);
}
		
