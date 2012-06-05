/********************* Ejemplo de listas enlazadas ***********************/
/*
   Este programa crea una lista enlazada cuyos nodos son números, y
   permite hacer las siguientes operaciones sobre ella:

   - Recorrer la lista de forma iterativa y recursiva.
   - Insertar un elemento en la lista manteniendo el orden ascendente.
   - Borrar un elemento de la lista.
   - Liberar la lista de forma iterativa y recursiva.
*/
/* Autor: Francisco Gaytán Muñoz <p92gamuf@uco.es> */
/* Web: http://www.uco.es/~p92gamuf */
/*************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Tipo abstracto de cada nodo de la lista */
struct nodolista
{
   int nodo;
   struct nodolista *siguiente;
};

/* Prototipos de funciones */
int menu(void);
void crear(struct nodolista **cabeza);
int vacia(struct nodolista *cabeza);
void listar(struct nodolista *cabeza,int opcion);
void visualizar(struct nodolista *cabeza);
void visualizarRecursivo(struct nodolista *actual);
void insertar(struct nodolista **cabeza);
void borrar(struct nodolista **cabeza);
void liberar(struct nodolista **cabeza);
void liberarRecursivo(struct nodolista **cabeza);
void grabar(struct nodolista *cabeza);
int grabarFichero(struct nodolista *cabeza, char *fichero);
void leer(struct nodolista **cabeza);
int leerFichero(struct nodolista **cabeza,char *nombre);

/* Programa principal */
main()
{
   struct nodolista *cabeza;
   int opcion;

   /* creamos la lista */
   crear(&cabeza);

   /* opciones */
   do
   {
      opcion=menu();
      switch(opcion)
      {
	 case 1: listar(cabeza,1);  /* normal */
		 break;
	 case 2: listar(cabeza,2);  /* recursivo */
		 break;
	 case 3: insertar(&cabeza);
		 break;
	 case 4: borrar(&cabeza);
		 break;
	 case 5: liberar(&cabeza);
		 break;
	 case 6: liberarRecursivo(&cabeza);
		 break;
	 case 7: grabar(cabeza);
		 break;
	 case 8: leer(&cabeza);
		 break;
      }
   } while (opcion);  /* opcion != 0 */
}

int menu(void)
{
   int opcion;

   printf("EJEMPLO DE LISTA ENLAZADA\n");
   printf("-------------------------\n\n");
   printf("1.- Listado de la lista (normal)\n");
   printf("2.- Listado de la lista (recursivo)\n");
   printf("3.- Insertar un elemento en la lista\n");
   printf("4.- Borrado de un elemento de la lista\n");
   printf("5.- Liberar la memoria ocupada por la lista (normal)\n");
   printf("6.- Liberar la memoria ocupada por la lista (recursiva)\n");
   printf("7.- Grabar la lista en un archivo\n");
   printf("8.- Leer la lista de un archivo\n\n");
   printf("0.- TERMINAR.\n\n\n");
   printf("Introduce una opción: ");
   scanf("%d",&opcion);
   fflush(stdin);
   return opcion;
}

/************************ Función crear() ***************************/
/*
   Propósito..: Crea la lista.
   Parámetros.: Puntero cabeza de lista por referencia.
   Devuelve...: Nada.
*/
/********************************************************************/
void crear(struct nodolista **cabeza)
{
   *cabeza = NULL;
}

/************************ Función vacia() ***************************/
/*
   Propósito:  Comprueba si la lista está vacía.
   Parámetros: Puntero cabeza de lista por valor.
   Devuelve:   1 si la lista está vacía.
               0 si no lo está.
*/
/********************************************************************/
int vacia(struct nodolista *cabeza)
{
   if (cabeza==NULL)
      return 1;    /* verdad */
   else
      return 0;    /* falso */
}

/************************ Función listar() ***************************/
/*
   Propósito:  Muestra por pantalla los elementos de la lista desde el
               principio al fin.
   Parámetros: Puntero cabeza de lista por valor.
               Recorrido recursivo (1) o no recursivo (2).
   Devuelve:   nada.
   Llama a la funciones visualizar() y visualizarRecursivo().
*/
/********************************************************************/
void listar(struct nodolista *cabeza,int opcion)
{
	printf("hola\n");
   /* si la lista está vacía no hacemos nada */
   if (vacia(cabeza))
      printf("\n\nLa lista está vacía.\n");
   else
   /* proceso normal (lista no vacía) */
   {
      /* cabecera */

      printf("LISTADO\n");
      printf("-------\n\n");

      /* proceso */
      if (opcion==1)   /* normal */
	 visualizar(cabeza);
      else
	 visualizarRecursivo(cabeza);
   }
   getchar(); 
}

/************************ Función visualizar() ***********************/
/*
   Propósito:  Muestra por pantalla los elementos de la lista desde el
               principio al fin de forma iterativa.
   Parámetros: Puntero cabeza de lista por valor.
   Devuelve:   Nada.
   Llamada por listar().
*/
/********************************************************************/
void visualizar(struct nodolista *cabeza)
{
   struct nodolista *actual;  /* recorre la lista */
   int n=0;

   actual = cabeza;
   while (actual!=NULL)
   {
      printf("%3d.- %d\n",++n,actual->nodo);
      actual = actual->siguiente;
   }
}

/******************** Función visualizarRecursivo() *****************/
/*
   Propósito:  Muestra por pantalla los elementos de la lista desde el
               principio al fin de forma recursiva.
   Parámetros: Puntero cabeza de lista por valor.
   Devuelve:   Nada.
   Llamada por listar().
*/
/********************************************************************/
void visualizarRecursivo(struct nodolista *actual)
{
   static int n=0;

   if (actual!=NULL)
   {
      printf("%3d.- %d\n",++n,actual->nodo);
      visualizarRecursivo(actual->siguiente);
   }
   else
      n=0;   /* para que la siguiente vez empiece en 0 */
}

/************************ Función insertar() ************************/
/*
   Propósito:  Pide un número al usuario y lo inserta como nodo en la
               lista de forma que se mantenga el orden ascendente de la
               misma.
   Parámetros: Puntero cabeza de lista por referencia.
   Devuelve:   Nada.
*/
/********************************************************************/
void insertar(struct nodolista **cabeza)
{
   struct nodolista *predecesor,*sucesor,*nuevo;

   printf("INSERCIÓN\n");
   printf("---------\n\n");

   /* creamos nodo */
   nuevo = (struct nodolista *) malloc(sizeof(struct nodolista));

   /* pedimos la información del nodo */
   printf("Introduzca nodo: ");
   scanf("%d",&nuevo->nodo); fflush(stdin);

   /* insertamos nodo */

   /* primero vemos si es un caso particular: lista vacía o inserción
      en la cabeza de la lista */
   if (vacia(*cabeza) || nuevo->nodo < (*cabeza)->nodo)
   {
      nuevo->siguiente = *cabeza;
      *cabeza = nuevo;
   }
   else  /* caso general */
   {
      predecesor = *cabeza;
      sucesor = predecesor->siguiente;
      while (sucesor!=NULL && sucesor->nodo <= nuevo->nodo)
      {
	 predecesor = sucesor;
	 sucesor = sucesor->siguiente;
      }
      predecesor->siguiente = nuevo;
      nuevo->siguiente = sucesor;
   }
}

/************************ Función borrar() ************************/
/*
   Propósito:  Pide un número al usuario, comprueba que es un elemento
               de la lista y en ese caso lo borra de la misma.
   Parámetros: Puntero cabeza de lista por referencia.
   Devuelve:   Nada.
*/
/********************************************************************/
void borrar(struct nodolista **cabeza)
{
   struct nodolista *anterior,*borrar;
   int nodoaborrar;

   /* si la lista está vacía no hacemos nada */
   if (vacia(*cabeza))
   {
      printf("\n\nLa lista está vacía.\n");
      getchar();
   }
   else
   /* proceso normal (lista no vacía) */
   {
      printf("BORRADO\n");
      printf("-------\n\n");

      /* pedimos la información del nodo a borrar */
      printf("Introduzca nodo a borrar: ");
      scanf("%d",&nodoaborrar); fflush(stdin);


      /* primero vemos si es un caso particular: borrar primero */
      if ((*cabeza)->nodo == nodoaborrar)
      {
	 borrar = *cabeza;
	 *cabeza = (*cabeza)->siguiente;
	 free(borrar);
      }
      else  /* caso general */
      {
	 /* buscamos el elemento a borrar */
	 anterior = *cabeza;
	 borrar = anterior->siguiente;
	 while (borrar!=NULL && borrar->nodo!=nodoaborrar)
	 {
	    anterior = borrar;
	    borrar = borrar->siguiente;
	 }

	 /* si el elemento está lo borramos */
	 if (borrar!=NULL)
	 {
	    anterior->siguiente = borrar->siguiente;
	    free(borrar);
	 }
	 else
	 {
	    printf("\n\nEl elemento %d no está en la lista.\n",nodoaborrar);
	    getchar();
	 }
      }
   }
}

/************************ Función liberar() *************************/
/*
   Propósito:  Libera la memoria ocupada por la lista de forma iterativa.
   Parámetros: Puntero cabeza de lista por referencia.
   Devuelve:   Nada.
*/
/********************************************************************/
void liberar(struct nodolista **cabeza)
{
   struct nodolista *actual,*sucesor;

   actual = *cabeza;
   while (actual!=NULL)
   {
      sucesor = actual->siguiente;
      free(actual);
      actual = sucesor;
   }
   *cabeza = NULL;
}

/******************* Función liberarRecursivo() *********************/
/*
   Propósito:  Libera la memoria ocupada por la lista de forma recursiva.
   Parámetros: Puntero cabeza de lista por referencia.
   Devuelve:   Nada.
*/
/********************************************************************/
void liberarRecursivo(struct nodolista **cabeza)
{
   struct nodolista *sucesor;

   if (*cabeza!=NULL)
   {
      sucesor = (*cabeza)->siguiente;
      liberarRecursivo(&sucesor);
      free(*cabeza);
      *cabeza = NULL;
   }
}

/************************ Función grabar() *****************************/
/*
   Propósito:  Grabar las lista en un fichero introducido por el usuario.
   Parámetros: Puntero cabeza de lista por valor.
   Devuelve:   Nada.
   Llama a la función grabarFichero().
*/
/***********************************************************************/
void grabar(struct nodolista *cabeza)
{
   char fichero[31];  /* nombre del archivo */

   /* si la lista está vacía no hacemos nada */
   if (vacia(cabeza))
   {
      printf("\n\nLa lista está vacía.\n");
      getchar();
   }
   else
   {
      printf("GRABAR EN ARCHIVO\n");
      printf("-----------------\n\n");

      /* pedimos nombre del fichero */

      printf("Nombre fichero: ");
      gets(fichero);

      /* Proceso */

      if (!grabarFichero(cabeza,fichero))
      {
         printf("\nError al guardar la lista.\n");
         getchar();
      }
   }
}

/*********************** Función grabarFichero() ************************/
/*
   Propósito:  Grabar la lista en un fichero pasado como parámetro.
   Parámetros: Puntero cabeza de lista por valor y nombre del fichero.
   Devuelve:   0 si no se ha podido hacer correctamente, 1 en caso contrario.
   Llamada por la función grabar().
*/
/***********************************************************************/
int grabarFichero(struct nodolista *cabeza, char *fichero)
{
   FILE *f;
   struct nodolista *actual=cabeza;
   
   /* En este ejemplo los registros del archivo son enteros, en cualquier
      otro caso serían los campos informativos de los nodos de la lista, aunque
      otra posibilidad sería grabar el nodo completo (con el apuntador), pero
      estaríamos guardando información innecesaria. */

   /* Abrir fichero */

   if ((f=fopen(fichero,"wb"))==NULL)
      return 0;

   /* Escribir la lista
     (para hacerlo así el apuntador debe ser el último campo)*/

   while (actual!=NULL)
   {
      fwrite(actual,sizeof(int),1,f);
      actual=actual->siguiente;
   }
   fclose(f);
   return 1;
}

/************************ Función leer() *****************************/
/*
   Propósito:  Leer la lista de un fichero introducido por el usuario.
               En el caso de que la lista tenga datos los añadirá al final.
   Parámetros: Puntero cabeza de lista por referencia.
   Devuelve:   Nada.
   Llama a la función leerFichero().
*/
/*********************************************************************/
void leer(struct nodolista **cabeza)
{
   char fichero[31];


   printf("LEER DE ARCHIVO\n");
   printf("---------------\n\n");

   /* pedimos nombre del fichero */

   printf("Nombre fichero: "); 
   gets(fichero);

   /* Proceso */

   if (!leerFichero(cabeza,fichero))
   {
      printf("\nError al leer el fichero.\n");
      getchar();
   }
}

/*********************** Función leerFichero() ************************/
/*
   Propósito:  Leer la lista de un fichero pasado como parámetro.
               Si la lista tiene datos, añade los del fichero al final.
   Parámetros: Puntero cabeza de lista por referencia y nombre del fichero.
   Devuelve:   0 si no se ha podido hacer correctamente, 1 en caso contrario.
   Llamada por la función leer().
   
   OJO!!! Al añadir registros como nodos no respetamos el orden, invitamos al
          alumno a que haga los cambios oportunos para que esto no sea así.
*/
/*********************************************************************/
int leerFichero(struct nodolista **cabeza,char *nombre)
{
   FILE *f;
   struct nodolista *actual=*cabeza;
   int registro;

   /* Abrir el archivo */

   if ((f=fopen(nombre,"rb"))==NULL)
      return 0;

   /* Ahora nos encontramos con la posibilidad (caso particular) de que la 
      lista esté vacía. En este caso leeremos el primer registro del archivo
      y crearemos un nodo en la lista al que apuntarán los punteros cabeza 
      y actual. De esta forma evitaremos considerar casos especiales dentro 
      del ciclo de lectura del fichero */

   if (vacia(*cabeza)) 
   {
      if (fread(&registro,sizeof(int),1,f))  /* hay registros */
      {
         *cabeza = (struct nodolista *) malloc(sizeof(struct nodolista));
	 (*cabeza)->nodo = registro;
	 (*cabeza)->siguiente = NULL;
	 actual = *cabeza;
      }
   }
   else  /* hay nodos en la lista */
      while (actual->siguiente!=NULL)
	 actual=actual->siguiente;

   /* ahora actual está en el último nodo de la lista */
   while (fread(&registro,sizeof(int),1,f))
   {
      actual->siguiente = (struct nodolista *) malloc(sizeof(struct nodolista));
      actual = actual->siguiente;
      actual->nodo = registro;
      actual->siguiente=NULL;
   }
   fclose(f);
   return 1;
}
