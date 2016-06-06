#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <errno.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>		

#define SERVER_IP 	"127.0.0.1"
#define	SERVER_PORT	5000
#define SERVER_LENGTH	10
#define SERVER_BUFF	20

int main()
{
	int sock_fd;
	int buffer_len, client_len;

	struct sockaddr_in serv_addr;
	struct sockaddr client_addr;

	char serv_buffer[SERVER_BUFF];

	printf("Server is waiting\n");

	//create a UDP Socket
	if( (sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
	{
		printf("Error: Could not create socket");
		return 1;
	}


	//bind it to a particular IP address & port
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
	//serv_addr.sin_addr.s_addr = INADDR_ANY; //macro value is 0.0.0.0, kernel will take the current IP address
	serv_addr.sin_port = htons(SERVER_PORT);
	//serv_addr.sin_port = 0; //kernel will take care of the endianess and will take the available port number
	
	bind(sock_fd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));

	//Try to get some actual data ffrom client i.e receive a message from a socket
	client_len = sizeof(struct sockaddr_in);	
	recvfrom(sock_fd, (void *)serv_buffer, SERVER_BUFF, 0, (struct sockaddr *)&client_addr, &client_len);

	//print the data received from client
	printf("Client data: \n %s", serv_buffer);

	printf("\n");
	//close the sockets now
	close(sock_fd);
	
}	

