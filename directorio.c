#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include "buscar.h"

int main(int c, char *v[]){
    int len,tipo,count;
    struct dirent *pDirent;
    DIR *pDir;

    if (c < 2) {
        printf ("Usage: testprog <dirname>\n");
        return 1;
    }
    pDir = opendir (v[1]);
    if (pDir == NULL) {
        printf ("Cannot open directory '%s'\n", v[1]);
        return 1;
    }

    while ((pDirent = readdir(pDir)) != NULL) {
        printf ("[%s]\n", pDirent->d_name);
        tipo = pDirent->d_type;
        if(tipo == 8){
			count = buscar(v[2],pDirent->d_name);
			if(count != -1){
				printf("el numero de veces que %s esta es %d\n",v[2],count);
			}else{
				continue;
			}
			
		}
    }
    closedir (pDir);
    return 0;
}
