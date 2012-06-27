#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include "buscar.h"

int main(int argc, char *argv[]){
    
    char temp[80];
    int len,tipo,count;
    struct dirent *pDirent;
    DIR *pDir;

    if (argc < 2) {
        printf("Usage: testprog <dirname>\n");
        return 1;
    }
    pDir = opendir(argv[1]);
    if (pDir == NULL) {
        printf("Cannot open directory '%s'\n", argv[1]);
        return 1;
    }

	printf("palabra: %s \n", argv[2]);
    while ((pDirent = readdir(pDir)) != NULL) {
        printf("[%s]\n", pDirent->d_name);
        tipo = pDirent->d_type;
        
        if (tipo == 8){
			strcpy(temp, argv[1]);
			strcat(temp, pDirent->d_name);
			count = buscar(argv[2], temp);
			if(count != -1){
				printf("El numero de veces que '%s' esta en %s es %d\n", argv[2], temp, count);
			} else {
				continue;
			}
			
		}
    }
    closedir (pDir);
    return 0;
}
