#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void main(){
	
	int t,i,pid,status,pid_h;
	printf("introdusca el numero de procesos\n");
	scanf("%d",&t);
	for(i = 0; i < t;i++){
		pid = fork();
		if(pid == 0){
			printf("soy el hijo con pid:%d, y mi padre es %d\n",getpid(),getppid());
			exit(0);		
			
		}
		
	}
	while((pid_h = wait(&status)) != -1 ){
		printf("soy el padre con pid:%d y el hijo que termino fue %d\n",getpid(),pid_h);
	
	}	
}
