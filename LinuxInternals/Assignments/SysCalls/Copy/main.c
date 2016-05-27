/*
 *	Assignment 1: my_copy.c
 *	Implement a cp(copy) command with –p option.
 *
 *	Pre-requisites:-
 *	 Knowledge about system calls, How to read and understand ‘man pages’.
 *	 Command line arguments, File operation system calls (open, read, write, close, fstat ..etc)
 *
 *	Objective: -
 *	 To understand and implement using basic system calls.
 *	
 * 	Requirements: -
 *	1. Copy source file to destination file which passed through cmd-line arguments. 
 *		After copying both files must have equal size, even it’s a zero sized file.
 *		Eg: - ./my_copy source.txt dest.txt.
 *	1. If arguments are missing show the usage (help) info to user.
 *	2. Implement a my_copy() function where you have to pass two file descriptors.
 *		Int my_copy(int source_fd, int dest_fd);
 *	3. If –p option passed copy permissions as well to destination (refer ‘fstat’ man page).
 *		Eg: - ./my_copy –p source.txt dest.txt.
 *	4. If the destination file is not present then create a new one with given name. 
 *		Incase if it is present show a confirmation from user to overwrite.
 *		Eg: - ./my_copy source.txt destination.txt
 *			File “destination.txt” is already exists.
 *			Do you want to overwrite (Y/n)
 *	5. If user type ‘Y/n’ or enter key overwrite the destination with new file. 
 *		In n/N don’t overwrite and exit from program.
 *	6. Program should able handle all possible error conditions.
 *
 *	Sample execution: -
 *	1. When no arguments are passed
 *	./my_copy
 *	Insufficient arguments
 *	Usage:- ./my_copy [option] <source file> <destination file>
 *
 *	2. When destination file is not exists
 *	./my_copy source.txt dest.txt
 *	New dest.txt file is created and source.txt file will be copied to dest.txt file
 *	
 *	3. When destination file exists
 *	./my_copy source.txt dest.txt
 * 	File “dest.txt” is already exists.
 *	Do you want to overwrite (Y/n)
 *	
 *	4. When –p option passed
 *	./my_copy –p source.txt dest.txt
 *	Permissions also copied from source file to destination file
 *	
 *	Also try:-
 *	5. ./my_copy /etc/hosts /etc/services
 *	6. ./my_copy /dev/zero /tmp/new
 *	
 *	Useful commands:-
 *	Man, cksum, ls –l
 */

#include "syscalls.h"

int main(int argc, char *argv[])
{
	int fd, fd2, read_len;
	char choice;
	
	//for -p to copy the permission mode
	struct stat sb;
	
	/* Do arg count check */
    	if (argc < 3)
    	{
        	printf("Insufficient arguments\n");
		printf("Usage:- ./my_copy [option] <source file> <destination file> \n");
        	return 1;
    	}
	
	/* check for -p permissions */
	if (strcmp(argv[1], "-p") == 0 )
	{
		printf("Permissions also copied from source file to destination file.\n");
		/* To open source.txt to read */
		if ( (fd = open(argv[2], O_RDONLY)) == -1 )
		{
			perror("open");
			return -1;	
		}
		
		//get the permission of this file
		//stat(argv[2], &sb);
		if (stat(argv[2], &sb) )
		{
			perror("stat");
			return -1;
		}
 
		/* To create/ open dest.txt to copy the data */
		if ( (fd2 = open(argv[3], O_WRONLY|O_CREAT|O_TRUNC, 0666)) == -1 )
		{
			
			printf("File %s is already exists.\n Do you want to overwrite (y/n): ", argv[2]);
			scanf("\n%c", &choice);
	
			if(choice == 'n' || choice == 'N')
			{
				return 0;
			}
			else if (choice == 'y' || choice == 'Y')
			{
				//for overwriting
				if ( (fd2 = creat(argv[3], 0666)) == -1 )
				{
					perror("open");
					return -1;	
				}	
			}
			
		}
		//change the permisions
		if (chmod(argv[3], sb.st_mode & 07777))
    		{
        		perror("chmod");
			return -1;
    		}
		
		
	}
	/* when no -p option is given */
	else
	{
		/* To open source.txt to read */
		if ( (fd = open(argv[1], O_RDONLY)) == -1 )
		{
			perror("open");
			return -1;	
		}	
	
		/* To create/ open dest.txt to copy the data */
		if ( (fd2 = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0666)) == -1 )
		{
			printf("File %s is already exists.\n Do you want to overwrite (y/n): ", argv[2]);
			scanf("\n%c", &choice);
	
			if(choice == 'n' || choice == 'N')
			{
				return 0;
			}
			else if (choice == 'y' || choice == 'Y')
			{
				//for overwriting
				if ( (fd2 = creat(argv[2], 0666)) == -1 )
				{
					perror("open");
					return -1;	
				}	
			}
			
		}			
	}	

	//copy appropraitely 
	my_copy(fd, fd2);
	
	close(fd);
	close(fd2);

	return 0;
}


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
			return -1;
		}
	}

	return 0;
}

