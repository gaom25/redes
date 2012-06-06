#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>


 struct est {									// Definicion de estructura estudiante
 	char nombre[51];
 	struct est *proximo;
 };
   
typedef struct est Lista;

void insertar(char palabras[], Lista **L)				// Procedimiento para insertar nuevo Lista
{
	   Lista *new;
	   Lista *prox = *L;
	   
	   new = (Lista *)malloc(sizeof (Lista));
	   
	   if (new == NULL) {							// Si la llamada al sistema retorna NULL es que la memoria 											esta llena y no puede albergas mas estructuras Estudiante
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


void agrpal (Lista **L, int mx[][2], int i)
{
		Lista *tmp;
		tmp = *L;
		char nomas[] = {"NOMAS"};
		if(tmp != NULL) {
			write(mx[i][1],tmp->nombre,strlen(tmp->nombre)+1);
			*L = (*L)->proximo;
			//free(tmp);
		}else{
			write(mx[i][1],nomas,strlen(nomas)+1);
		}
}			


int imprimir (Lista **L)
{
	Lista *tmp;
	tmp = *L;
	int i=0;
	
	while (tmp->proximo != NULL)
	{
		printf("palabra: %s \n", tmp->nombre);
		tmp = tmp->proximo;
		i++;
	}
	return i;
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
		
