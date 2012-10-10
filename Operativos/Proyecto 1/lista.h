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

/* Definición de la lista */
 struct est {									
 	char nombre[51];
 	struct est *proximo;
 };
   
typedef struct est Lista;

/* Procedimiento para insertar una nueva palabra en la lista */
void insertar(char palabras[], Lista **L)				
{
	Lista *new;
	Lista *prox = *L;
	   
	new = (Lista *)malloc(sizeof (Lista));
	   
	if (new == NULL) {
		printf("Memoria llena\n");
	} else {
		strcpy(new->nombre, palabras);
		new->proximo = NULL;
		 
	    if (prox == NULL) {
			*L = new; 
		} else {
			while ((prox->proximo) != NULL) {
				prox = prox->proximo;
	       }
	       prox->proximo = new;
		}
	}
}

/* Procedimiento para escribir en el pipe la palabra de la estructura */
void agrpal (Lista **L, int **mx, int i)
{
		Lista *tmp;
		tmp = *L;
		
		if(tmp != NULL) {
			write(mx[i][1],tmp->nombre,strlen(tmp->nombre)+1);
			*L = (*L)->proximo;
		} else {
			write(mx[i][1],"NOMAS",6);
		}
}			

liberar(Lista **cabeza){
		Lista *rm;
		rm = *cabeza;
		if(*cabeza != NULL) {
			*cabeza = (*cabeza)->proximo;
		
			while(*cabeza != NULL){
				free(rm);
				rm = *cabeza;
				*cabeza = (*cabeza)->proximo;
				}
		}
}
		
