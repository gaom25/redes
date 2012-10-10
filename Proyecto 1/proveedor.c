#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include "funciones.h"

int main(int argc, char *argv[])
{
	int sockfd, clientsockfd, numport;
	socklen_t clientlen;
	char buffer[256];
	struct sockaddr_in dirserv, dirclient;
	int n;
	char prod[50]

	comprobacion(argc, argv);

	// Se crea el socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0){
		printf("Error creando el socket\n");
		exit(1);
	}
	
	bzero((char *) &dirserv, sizeof(dirserv));	// Se limpia la estructura
    numport = atoi(argv[4]);					// Se obtiene el numero de puerto
    
    // Se llena la estructura de datos del servidor
    dirserv.sin_family = AF_INET;
    dirserv.sin_addr.s_addr = INADDR_ANY;
    dirserv.sin_port = htons(numport);
     
    /* Hace el bind, es decir, asigna la direccion especificada al socket
     * a traves de su fd */
    if (bind(sockfd, (struct sockaddr *) &dirserv, sizeof(dirserv)) < 0) {
		printf("Error haciendo el bind\n");
		exit(1);
    }
     
    // Se pone a escuchar por las peticiones, 5 es el numero maximo???      
    listen(sockfd,5);
    clientlen = sizeof(dirclient);
     
    // Acepta la conexion y se crea un fd asociado a ese cliente
    clientsockfd = accept(sockfd, (struct sockaddr *) &dirclient, &clientlen);
     
    if (clientsockfd < 0) {
		printf("Error aceptando peticion\n");
        exit(1);
    }
     
    /* Se limpia el buffer y se lee lo que se pase por el fd*/
	bzero(buffer,256); 				
    n = read(clientsockfd, buffer, 255);
     
	if (n < 0) {
		printf("Error leyendo del socket\n");
		exit(1);
	}
	
	printf("Obtuve del cliente: %s\n", buffer);
	
	/* Si se especifica la opcion -a, el cliente le envia al servidor
	 * el flag "I", que significa que solo buscara en su inventario el
	 * producto pedido por el cliente */
	if (strcmp(buffer, "I") == 0) {
		n = write(newsockfd,"Recibi el mensaje",17);
		if (n < 0) {
			printf("ERROR writing to socket");
			exit(1);
		}
		
		bzero(buffer,256);
		n = read(clientsockfd, buffer, 255);
     
		if (n < 0) {
			printf("Error leyendo del socket\n");
			exit(1);
		}
		
		strcpy(prod,buffer);	
	}
     
    
    	
}
     
     
