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
	int sock_fd, data_sock_fd;
	int buffer_len;
	pid_t pid;


	struct sockaddr_in serv_addr;
	char serv_buffer[SERVER_BUFF];

	printf("Server is waiting\n");

	//create a TCP Socket
	if( (sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{
		printf("Error: Could not create socket");
		return 1;
	}


	//bind it to a particular IP address & port
	serv_addr.sin_family = AF_INET;
	//serv_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(SERVER_PORT);

	bind(sock_fd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));

	//wait and listen for incoming connections
	listen(sock_fd, SERVER_LENGTH);

	//get into infinte loop as this is a server
	while(1)
	{
		//if there are any, accept and create a new data socket
		//accept returns means TCP threeway handshake (SYN-ACK-SYN) successsful
		// the new socket (second socket) is data connection. For every client now 
		// we need to for a child in order to handle seperate connections
		data_sock_fd = accept(sock_fd, (struct sockaddr*) NULL, NULL);

		pid = fork();
		if(pid == 0)
		{
			printf("new child forked ... awaiting for input from client\n");
			
			while(1)
			{
				//Try to get some actual data ffrom client i.e receive a message from a socket
				recv(data_sock_fd, (void *)serv_buffer, SERVER_BUFF, 0);
				
				//print the data received from client
				printf("Client %d data: %s", getpid(), serv_buffer);

				printf("\n");
			}
	
			//close the sockets now
			close(data_sock_fd);

			//let the child exit
			exit(0);
		}
			
	}

	//it doesnt get here, incase it gets close the control socket
	close(sock_fd);
	
}	

