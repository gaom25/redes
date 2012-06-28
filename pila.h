struct est {									
 	char nombre[51];
 	struct est *proximo;
 };
   
typedef struct est Pila;

void empilar(char palabras[], Pila **L);
void desempilar(char palabra[],Pila **L);
