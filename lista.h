#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>


 struct est {									// Definicion de estructura estudiante
 	char nombre[51];
 	struct est *proximo;
 };
   
typedef struct est Lista;

void insertar(char palabras[], Lista *L)				// Procedimiento para insertar nuevo Lista
{
	   Lista *new;
	   Lista *prox = L;
	   
	   new = (Lista *)malloc(sizeof (Lista));
	   
	   if (new == NULL) {							// Si la llamada al sistema retorna NULL es que la memoria 											esta llena y no puede albergas mas estructuras Estudiante
	     printf("Memoria llena, no se pueden ingresar mas estudiantes\n");
	   } else {
	     strcpy(new->nombre, palabras);
	     new->proximo = NULL;
		 
	     if (prox == NULL) {
	        prox = new; 
		} else {
			while ((prox->proximo) != NULL) {
				prox = prox->proximo;
	       }
	       prox->proximo = new;
		}
		}
}

void agrpal (Lista *L, int **mx, int i)
{
		Lista *tmp;
		tmp = L;
		close(mx[i][0]);
		write(mx[i][1],L->nombre,strlen(L->nombre)+1);
		close(mx[i][1]);
		L = L->proximo;
		free(tmp);
}			
