#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct def {									// Definicion de estructura estudiante
 	char nombre[51];
 	int pid;
 	struct def *proximo;
 };
 
typedef struct def Listap;
 
void insertarp(char palabras[],int a, Listap **L)				// Procedimiento para insertar nuevo Lista
{
	   Listap *new;
	   Listap *prox = *L;
	   
	   new = (Listap *)malloc(sizeof (Lista));
	   
	   if (new == NULL) {							// Si la llamada al sistema retorna NULL es que la memoria 											esta llena y no puede albergas mas estructuras Estudiante
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

void busprt(Listap **cabeza, int p){
	Listap *tmp;
   tmp = *cabeza;

   /* si la lista está vacía no hacemos nada */
   if (*cabeza == NULL){
      printf("\n\nLa lista está vacía.\n");
   }
   else                                          /* proceso normal (lista no vacía) */
   {
		while(tmp->pid != p){
			tmp = tmp->proximo; 	
		}
      printf("%s ",tmp->nombre);
      
  		while(tmp != NULL){
  			if(tmp->pid == p) {
  				printf(",%s ",tmp->nombre);
				tmp = tmp->proximo;
			}
			tmp = tmp->proximo;
		}
      
    }	
}

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

	
	