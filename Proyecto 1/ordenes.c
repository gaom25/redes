#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include "funciones.h"

/* Estructura en la que se almacena la informacion de los proveedores 
 * con respecto a la consulta realizada */
typedef struct {
	char nombre[20];
	char hostname[50];
	char producto[30];
	int numport;
	int cantidad;
	int precio;
} proveedores;

int main(int argc, char *argv[])
{
	int sockfd, n;
    struct sockaddr_in dirserv;
    struct hostent *server;
    char buffer[256], archivo[50];
	char *pal_archivo;
	FILE *fd;
	size_t len;
	size_t read;
	
	*pal_archivo = NULL;
	/* Se comprueban los argumentos pasados */
	comprobacion(argc, argv);
	
	/* Se obtiene del usuario el archivo con la informacion de los
	 * proveedores y se guarda en archivo */
	strcpy(archivo, argv[5]);
	
	      
    // Se crea el socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sockfd < 0) {
       printf("ERROR opening socket");
       exit(1);
    }
	
	/* Se abre el archivo con la informacion de los proveedores para
	 * conectarse a ellos */
	
	fd = fopen(archivo, "r");
	if (fd == NULL) {
		printf("No se pudo abrir el archivo %s\n", archivo);
		exit(1);
	}

	/* Se lee el archivo y se extraen los datos a traves de los
	 * delimitadores de campo */
	
	read = getdelim(&pal_archivo, &len, '&', fd);
	
	if (pal_archivo[strlen(pal_archivo)-1] == '&')
		pal_archivo[strlen(pal_archivo)-1] = '\0';
		
	 // !! Meter el nombre del proveedor en la estructura !!
	 	
		
	while((read = getdelim(&pal_archivo,&len,'&',fd))!= -1)
	{
		
			if (pal_archivo[strlen(pal_archivo)-1] == '&')
				pal_archivo[strlen(pal_archivo)-1] = '\0';
				
			if (pal_archivo[strlen(pal_archivo)-1] == ' ')
				pal_archivo[strlen(pal_archivo)-1] = '\0';
				
			if (pal_archivo[strlen(pal_archivo)-1] == '\n')
				pal_archivo[strlen(pal_archivo)-1] = '\0';	
				
			memmove(pal_archivo, pal_archivo+1, strlen(pal_archivo));
				
		printf("%s3\n",pal_archivo);
		
	}
	free(pal_archivo);
	
 
	 
	 
	
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    
    // bcopy(*src, *dst, size)
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    
	//serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(portno);
    
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
        error("ERROR connecting");
    }
