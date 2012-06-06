#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

// Definicion de la lista
 struct est {									
 	char nombre[51];
 	struct est *proximo;
 };
   
typedef struct est Lista;

// Procedimiento para insertar nuevo Lista
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


void agrpal (Lista **L, int mx[][2], int i)
{
		Lista *tmp;
		tmp = *L;
		if(tmp != NULL) {
			write(mx[i][1],tmp->nombre,strlen(tmp->nombre)+1);
			*L = (*L)->proximo;
			//free(tmp);
		}else{
			write(mx[i][1],"NOMAS",6);
		}
}			

void imprimir (Lista **L)
{
	Lista *tmp;
	tmp = *L;
	int i=0;
	
	while (tmp->proximo != NULL)
	{
		printf("palabra: %s \n", tmp->nombre);
		tmp = tmp->proximo;
	}
}		
		
