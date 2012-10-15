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
	/* "sockfd" es el file descriptor asociado al socket, "clientsockfd"
	 * es el file descriptor asociado al cliente, "numport" es el numero 
	 * de puerto especificado por el usuario, "n" es utilizado para
	 * verificar si las llamadas al sistema dieron error */
	int sockfd, clientsockfd, numport, n;
	
	socklen_t clientlen;
	struct sockaddr_in dirserv, dirclient;
	
	/* "buffer" almacena los caracteres que se envia a traves del socket,
	 * "prod" contiene el producto a buscar que envia el cliente, "archivo"
	 * tiene la ruta del archivo inventario, "pal_archivo" es un arreglo 
	 * de caracteres donde se almacena cada palabra leida del texto, 
	 * "info" contiene toda la informacion del producto encontrado en
	 * el inventario */
	char buffer[256], prod[100], archivo[70], pal_archivo[50], info[50];
	
	FILE *fd;
	

	/* Se comprueban los argumentos pasados */
	comprobacion(argc, argv);
	
	/* Se obtiene la ruta del archivo inventario y el numero de puerto
	 * especificado por el usuario */
	numport = atoi(argv[4]);
	strcpy(archivo, argv[2];

	/* Se crea el socket */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0){
		printf("Error creando el socket\n");
		exit(1);
	}
	
	/* Se limpia la estructura */
	bzero((char *) &dirserv, sizeof(dirserv));
      
    /* Se llena la estructura de datos del servidor */
    dirserv.sin_family = AF_INET;
    dirserv.sin_addr.s_addr = INADDR_ANY;
    dirserv.sin_port = htons(numport);
     
    /* Hace el bind, es decir, asigna la direccion especificada al socket
     * a traves de su fd, y se verifica si se produjo un error */
    if (bind(sockfd, (struct sockaddr *) &dirserv, sizeof(dirserv)) < 0) {
		printf("Error haciendo el bind\n");
		exit(1);
    }
     
    /* Se pone a escuchar por las peticiones */     
    listen(sockfd,5);
    clientlen = sizeof(dirclient);
     
    /* Acepta la peticiendo de conexion y se crea un fd asociado a ese 
     * cliente, verificando si se produjo un error */
    clientsockfd = accept(sockfd, (struct sockaddr *) &dirclient, &clientlen);
    if (clientsockfd < 0) {
		printf("Error aceptando peticion\n");
        exit(1);
    }
     
    /* Se limpia el buffer y se lee lo que el cliente pase por el fd */
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
		n = write(clientsockfd,"Recibi el mensaje",17);
		if (n < 0) {
			printf("Error escribiendo en el socket");
			exit(1);
		}
		
		/* Se queda esperando que el cliente le envie todos los productos
		 * en su lista de peticiones */
		while (1) {
			/* Se limpia el buffer y se lee el producto a buscar
			 * enviado por el cliente */
			bzero(buffer,256);
			n = read(clientsockfd, buffer, 255);
			
			if (n < 0) {
				printf("Error leyendo del socket\n");
				exit(1);
			}
			
			
			strcpy(prod, buffer);
			/* Verifica si el cliente ya no va a mandar mas productos y 
			 * se sale del ciclo */
			if strcmp(prod, "NOMAS") {
				break;
			}	
			
			/* Busca el producto en su inventario. Abre el archivo inventario 
			 * pasado como argumento */
			fd = fopen(archivo, "r");
			if (fd == NULL) {
				printf("No se pudo abrir el archivo %s\n", archivo);
				exit(1);
			}

			/* Lee las palabras del archivo y las compara con la palabra 
			 * a buscar enviada por el cliente */
			fscanf(fd, "%s", pal_archivo);
			while (!feof(fd)) {
				/* Si encuentra el producto, le envia la informacion al
				 * cliente, y se queda esperando por otro producto.
				 * NOTA: AQUI DEBERIA DEJAR DE LEER Y RESETEAR EL FD DEL
				 * ARCHIVO PARA QUE COMIENCE A BUSCAR EL SIGUIENTE PRODUCTO
				 * DESDE EL PRINCIPIO. ESTO NO SE COMO SE HACE!!! */
				if (strcmp(pal_archivo, prod) == 0) {
					/* ¡¡¡¡ Hay 2 opciones: 
					 * 1) Que siga leyendo esa linea hasta que encuentre 
					 * el \n y todo eso se lo pasa al cliente. Esto creo 
					 * que se haria con fgets, pero fgets tomaria
					 * a partir de donde lei la ultima vez con fscanf, es
					 * decir, no envia el nombre del producto. Esto se puede
					 * solucionar conCATEnando prod+info. NOTA: fgets agarra
					 * incluyendo el \n !!! */
					 
					fgets(info, 50, fd);
					strcat(prod, info);
					  
					n = write(clientsockfd, prod, 100);
					if (n < 0) {
						printf("Error escribiendo en el socket");
						exit(1);
					}
					  
					/* 2) Que siga leyendo hasta el primer &, y le escribe
					 * al cliente el nombre del producto, luego lee hasta
					 * el 2do & y asi */
					 
					/* ¡¡¡No se si hacer break para no seguir leyendo el 
					 * archivo!!!!! */
					 // break;
				}
				fscanf(fd, "%s", pal_archivo);
			}
			
			// AQUI SE RESETEARIA EL FD DEL ARCHIVO, I THINK
		}
		fclose(fd);		
	}
     
    
    	
}
     
     
