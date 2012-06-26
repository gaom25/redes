/********************************************/
/*				 Proyecto 1					*/
/********************************************/
/*			Gustavo Ortega 09-10590			*/
/*		   Katrin Bethencourt 09-10102		*/
/********************************************/

/********************************************/
/* Header que crea la lista utilizada para  */
/*   guardar la palabra que buscó el hijo,	*/
/*   		con su respectivo PID 	        */
/********************************************/

#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

/* Define la lista */
struct def {
 	char nombre[51];
 	int pid;
 	struct def *proximo;
 };
 
typedef struct def Listap;

/* Procedimiento para insertar nuevo elemento a la lista */
void insertarp(char palabras[],int a, Listap **L)				
{
	   Listap *new;
	   Listap *prox = *L;
	   
	   new = (Listap *)malloc(sizeof (Lista));
	   
	   if (new == NULL) {
	     printf("Memoria llena\n");
	   } else {
	     strcpy(new->nombre, palabras);
	     new->pid = a;
	     new->proximo = NULL;
		 
	     if (prox == NULL) {
	        *L = new; 
		  }else {
			while ((prox->proximo) != NULL) {
				prox = prox->proximo;
	       }
	       prox->proximo = new;
		  }
		}
}

/* Imprime las palabras que coincidan con el PID */
void busprt(Listap **cabeza, int p){
	Listap *tmp;
	tmp = *cabeza;

   /* Si la lista está vacía se indica */
	if (*cabeza == NULL){
		printf("La lista esta vacia\n");
	} else {
		while(tmp->proximo != NULL && tmp->pid == p) {
			printf("%s\n",tmp->nombre);
			tmp = tmp->proximo;
		}
      
    }	
}

/* Libera los apuntadores */
liberarp(Listap **cabeza){
	Listap *rm;
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

	
	
