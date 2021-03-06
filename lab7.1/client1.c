/*  Make the necessary includes and set up the variables.  */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct {
	char oper;
	int values[10];
} pack;



int main(int argc, char **argv)
{
	int sockfd;
	int len;
	struct sockaddr_un address;
	int resultado;
	char ch = 'A';

	/*  Create a socket for the client.  */

	sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

	/*  Name the socket, as agreed with the server.  */

	address.sun_family = AF_UNIX;
	strcpy(address.sun_path, "server_socket");
	len = sizeof(address);

	/*  Now connect our socket to the server's socket.  */

	resultado = connect(sockfd, (struct sockaddr *)&address, len);

	if (resultado == -1) {
		perror("oops: client1");
		exit(1);
	}

	/*  We can now read/write via sockfd.  */

	pack p;
	int i;

	p.oper = *argv[1];


	for (i = 2; i<argc;i++) {
		p.values[i - 2] = atoi(argv[i]);
	}




	write(sockfd, &p, sizeof(pack));
	printf("Client1: Done \n");
	close(sockfd);
	exit(0);
}