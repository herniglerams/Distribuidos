#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
 int sock_pasivo, sock_datos;
 struct sockaddr_in d_local;
 int leidos;
 int puerto = atoi(argv[1]);
 char mensaje[100];

 sock_pasivo = socket(PF_INET, SOCK_STREAM, 0);
 d_local.sin_family = AF_INET;
 d_local.sin_addr.s_addr = htonl(INADDR_ANY);
 d_local.sin_port = htons(puerto);

 bind(sock_pasivo, (struct sockaddr *)&d_local, sizeof(d_local));
 listen(sock_pasivo, SOMAXCONN);
 while (1) { // Bucle infinito de atención a clientes
  sock_datos = accept(sock_pasivo, 0, 0);
  while((leidos=read(sock_datos,mensaje,sizeof(mensaje)))>0){
  	send(sock_datos, mensaje, leidos,0);
  }
  close(sock_datos);
 }
}
