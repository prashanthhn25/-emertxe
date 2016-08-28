#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PORT 5000
#define MAXMSG 512
#define SERVER_IP 	"127.0.0.1"

int read_from_client(int filedes)
{
	char buffer[MAXMSG];
	int nbytes;

	nbytes = read(filedes, buffer, MAXMSG);

	if(nbytes < 0)
	{
		//read error
		perror("read");
		exit(EXIT_FAILURE);
	}
	else if(nbytes == 0)
	{
		//end of file
		return -1;
	}
	else
	{
		//data read
		printf("Server: got message: '%s' \n", buffer);
		return 0;
	}	
}

int make_socket(short port)
{
	int sock;
	struct sockaddr_in name;

	//create the socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
		
	if(sock < 0)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}

	//give the socket a name
	name.sin_family = AF_INET;
	name.sin_port = htons(port);
	name.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if(bind(sock, (struct sockaddr *) &name, sizeof(name)) < 0)
	{	
		perror("bind");
		exit(EXIT_FAILURE);
	}	

	return sock;
}

int main()
{
	int sock;
	fd_set active_fd_set, read_fd_set;
	
	int i;
	struct sockaddr_in clientname;
	socklen_t size;

	printf("Server is waiting\n");

	//create the socket and set it up to accept connections
	sock = make_socket(PORT);

	if(listen(sock, 1) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}

	//initialize the set of active sockets
	FD_ZERO(&active_fd_set);
	FD_SET(sock, &active_fd_set);

	while(1)
	{
		read_fd_set = active_fd_set;

		//block until input arrives on one or more active sockets
		if(select(FD_SETSIZE, &read_fd_set, NULL, NULL, NULL) < 0)
		{
			perror("select");
			exit(EXIT_FAILURE);	
		}

		//service all the sockets with input pending
		for(i = 0; i < FD_SETSIZE; ++i)
		{
			if(FD_ISSET(i, &read_fd_set))
			{
				//connection request on original socket
				if(i == sock)
				{
					int new;
					size = sizeof(clientname);
					new = accept(sock, (struct sockaddr *)&clientname, &size);

					if(new < 0)	
					{
						perror("accept");
						exit(EXIT_FAILURE);	
					}	
					printf("SERVER: connect from host %s, port %d. \n", inet_ntoa(clientname.sin_addr), ntohs(clientname.sin_port));
					FD_SET(new, &active_fd_set);
				}				
				else
				{
					//data arriving on an already- connected socket
					if(read_from_client(i) < 0)
					{
						close(i);
						FD_CLR(i, &active_fd_set);
					}
				}		
			}	
		}


	}	
	
}

