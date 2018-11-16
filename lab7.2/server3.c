/*  Make the necessary includes and set up the variables.  */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int server_sockfd, client_sockfd;
	int server_len, client_len;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;
	int client_id;
	time_t rawtime;
	struct tm * timeinf;
	char time_str[50];
	/*  Remove any old socket and create an unnamed socket for the server.  */

	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

	/*  Name the socket.  */

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(9734);
	server_len = sizeof(server_address);
	bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

	/*  Create a connection queue and wait for clients.  */

	listen(server_sockfd, 5);
	while (1) {
		char ch;

		printf("server waiting\n");

		/*  Accept a connection.  */

		client_len = sizeof(client_address);
		client_sockfd = accept(server_sockfd,
			(struct sockaddr *)&client_address, &client_len);

		/*  We can now read/write to client on client_sockfd.  */

		read(client_sockfd, &client_id, sizeof(int));
		printf("Server: the client_id is %d\n", client_id);

		/* Get the current time */
		time(&rawtime);
		timeinf = localtime(&rawtime);
		sprintf(time_str, "%s", asctime(timeinf));
		printf("Server: Current local time and date: %s\n", time_str);
		write(client_sockfd, &time_str, sizeof(time_str));
		close(client_sockfd);
	}
}