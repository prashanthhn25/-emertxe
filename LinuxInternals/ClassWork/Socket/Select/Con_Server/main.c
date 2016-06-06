#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arps/inet.h>
#include <netdb.h>

#define PORT 5555
#define MAXMSG 512

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

int make_socket(short port[])
{
}

int main()
{
	int sock;
	fd_set active_fd_set, read_fd_set;
	
	int i;
}

