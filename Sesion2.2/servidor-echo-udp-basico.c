#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h> // Necesario para strlen

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Uso: %s <puerto>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int sock_dat, recibidos;
    struct sockaddr_in d_local, d_cliente;
    socklen_t ldir = sizeof(d_cliente);
    char buffer[50];
    int puerto = atoi(argv[1]);
    sock_dat = socket(PF_INET, SOCK_DGRAM, 0);
    d_local.sin_family = AF_INET;
    d_local.sin_addr.s_addr = htonl(INADDR_ANY);
    d_local.sin_port = htons(puerto);
    bind(sock_dat, (struct sockaddr *)&d_local, sizeof(d_local));

    while (1) { // Bucle infinito 
        recibidos = recvfrom(sock_dat, buffer, sizeof(buffer), 0,
                             (struct sockaddr *) &d_cliente, &ldir);
        printf("Cliente desde %s (%d)\n",
               inet_ntoa(d_cliente.sin_addr), ntohs(d_cliente.sin_port));
        
        sendto(sock_dat, buffer, recibidos, 0,
               (struct sockaddr *) &d_cliente, ldir);
    }

    close(sock_dat); 
    return 0;
}
