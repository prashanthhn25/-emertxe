//scanf with time out using select

#include <stdio.h>
#include <unistd.h>

#include <sys/time.h>
#include <sys/types.h>

int main()
{
	//1. sets
	fd_set rfds;
	struct timeval tv;
	int retval;
	char buff[11];

	//watch stdin (fd 0 ) to see when it has input
	//2. clear set
	FD_ZERO(&rfds);
	
	//3. set [store values in set]
	FD_SET(0, &rfds);

	//wait up to 5 sec
	tv.tv_sec = 5;
	tv.tv_usec = 0;

	printf("Enter the string in 5 sec\n");
		
	retval = select(1, &rfds, NULL, NULL, &tv);
	//dont relay on tv value

	if(retval == -1)
	{
		perror("select()");
	}
	else if(retval)
	{
		//for multiple values eg: fd_set rfds[4];
		//for(int i = 0; i< 4; i++)
		//{
		//FD_ISSET(i, &rfds) 
		//}

		//FD_ISSET(0, &rfds) will be true
		read(0, buff, 10);
	}	
	else
	{
		printf("No data within 5 sec\n");
	}

	printf("Entered data: %s\n", buff);
	return 0;

}
