#include "syscalls.h"

int my_copy(int source_fd, int dest_fd)
{
	int read_len = 0;
	char buff[BUFF_SIZE]; 
	
	//read the data from the source.txt till end and copy
	while( ((read_len = read(source_fd, buff, BUFF_SIZE)) != -1 ) && (read_len != 0))
	{
		if( write(dest_fd, buff, read_len) == -1 )
		{
			perror("write");
			close(source_fd);
			close(dest_fd);
			return FAILURE;
		}
	}

	return SUCCESS;
}
