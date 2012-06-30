
#include <stdio.h>
#include <pthread.h>
#define NTHREADS 10
typedef struct{
		char archivo[50];
		int esta;
		int sali;
}manejador;


void *PrintHello(void *datos)
{	manejador *temp = datos;
	int tid;
	while(temp->esta == 1){
	printf("Hello World!, thread #%s!,and %ld\n",temp->archivo,pthread_self());
	temp->sali = 1;
	}
}


void main(int argc, char *argv[]){
	if(argc < 2){
		printf("Error en numero de argumentos\n");

	}else{
	int y,z;
	long i;
	printf("Cuantos hilos desea:\n");
	scanf("%d",&y);
	char hola[] = {"hola"};
	char chao[] = {"chao"};
	manejador datos[y];
	pthread_t threads[y];
	for(i = 0; i< y; i++){
		strcpy(datos[i].archivo,hola);
		datos[i].esta = 1;
		z = pthread_create(&threads[i],NULL,PrintHello,&datos[i]);
		if(z){
			printf("ERROR; return code from pthread_create() is %d\n", z);	
		}	
	}
	while(datos[i].sali != 1){
			i = (i+1)%y;
	}
	
	for(i = 0; i<y;i++){
		strcpy(datos[i].archivo,chao);
	}
	for(i = 0;i<y;i++){
		datos[i].esta = 0;
		pthread_join(threads[i],NULL);
	}
	pthread_exit(NULL);
	}
	
}
 
