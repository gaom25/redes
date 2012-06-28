
#include <stdio.h>
#include <pthread.h>

int x = 0;

void *PrintHello(void *threadid)
{
   long tid;
   tid = (long)threadid;
   printf("Hello World! It's me, thread #%ld!\n", tid);
   x = x + 1;
   printf("el numero es %d \n", x);
   pthread_exit(NULL);
}


void main(){
	int x,y,z;
	x = 0;
	long i;
	printf("Cuantos hilos desea:\n");
	scanf("%d",&y);
	pthread_t threads[y];
	for(i = 0; i< y; i++){
		z = pthread_create(&threads[i],NULL,PrintHello,(void *)i);
		if(z){
			printf("ERROR; return code from pthread_create() is %d\n", z);	
		}
		
	}
	pthread_exit(NULL);
	
}
 
