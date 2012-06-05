#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void main(){
	system("clear");
	int t,i,bytesleidos;
	char mensaje[100];
	char *frase = "veamos si funcionagfkdshgfdjks";
	printf("introdusca tamaño de la matriz \n");
	scanf("%d",&t);
	int ma[t][2];
	char pid[3][50];
	//strcpy(pid[0],"veamos");
	for(i = 0; i < sizeof("hola")+1;i++){
	strcpy(&pid[1][i],"hola");
	}
	//printf("%s\n",pid[0]);
	printf("%s\n",pid[1]);
	for(i = 0; i < t; i++){
		pipe(ma[i]);		
	}
	if(fork() == 0){
		close(ma[0][0]);
		write(ma[0][1],frase,strlen(frase));
		close(ma[0][1]);	
		
	}else
       {
       close (ma[0][1]);
       bytesleidos = read(ma[0][0], mensaje, 100);
       printf ("Bytes leidos: %d\n",bytesleidos);
       printf ("Mensaje: %s\n", mensaje);
       close (ma[0][0]);
       }
	
	
}