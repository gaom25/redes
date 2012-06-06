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
		if(tmp != NULL) {
			close(mx[i][0]);
			write(mx[i][1],tmp->nombre,strlen(tmp->nombre)+1);
			close(mx[i][1]);
			tmp = tmp->proximo;
			//free(tmp);
		}else{
			close(mx[i][0]);
			write(mx[i][1],"NOMAS",6);
			close(mx[i][1]);
		}
}			

int imprimir (Lista **L)
{
	Lista *tmp;
	tmp = *L;
	int i=0;
	
	while (tmp->proximo != NULL)
	{
		//printf("palabra: %s \n", tmp->nombre);
		tmp = tmp->proximo;
		i++;
	}
	return i;
}		
		
