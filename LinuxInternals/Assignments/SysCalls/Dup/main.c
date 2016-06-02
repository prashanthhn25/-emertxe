/*
 *	Assignment 3: dup.c
 *	Write a program to understand usage of dup and dup2 system calls.
 *
 *	Pre-requisites:-
 *	 Knowledge about system calls, How to read and understand ‘man pages’.
 *	 Command line arguments, File operation system calls (open, read, write, close ..etc)
 *	 Working of dup system calls.
 *
 *	Objective: -
 *	 To understand and implement using basic system calls.
 *	
 *	Requirements: -
 *	1. Using dup or dup2 redirect printf out to a given file instead of printing to stdout.
 *	2. Pass the file name using command-line arguments.
 *	3. Try using both system calls (dup and dup2).
 */

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	int fd;

	/* Do arg count check */
    	if (argc < 2)
    	{
        	printf("Insufficient arguments\n");
		printf("Usage:- ./my_dup <file> \n");
        	return 1;
    	}	
	
	/* open the file to which the redirection has to happen */
	if ( (fd = open(argv[1], O_APPEND|O_WRONLY)) == -1 )
	{
		perror("open");
		return -1;	
	}
		
	//close the stdout first
	close(1);

	/* point stdout to current file using dup2
	 * stdout(1) points to the descriptor of file even though it's still 1, 
	 * but the output is redirected now.
   	 */
	
	if (dup2(fd,1) < 0)
	{
		perror("ERROR: dup2 failed!");
		return -1;
	}
	
	printf("dup2: This should be in the file and not on the screen\n");

	/*
	 * the old descriptor is closed with dup2()
	 * With this particular call, we have the close operation, and the actual descriptor duplication, 
	 * wrapped up in one system call. 
	 * In addition, it is guaranteed to be atomic, which essentially means that it will never be 
 	 * interrupted by an arriving signal. The entire operation will transpire before returning control to the
	 * kernel for signal dispatching. With the original dup() system call, programmers had to perform a close()
	 * operation before calling it. That resulted in two system calls, with a small degree of vulnerability in the
	 * brief amount of time which elapsed between them. If a signal arrived during that brief instance, the
	 * descriptor duplication would fail. Of course, dup2() solves this problem for us.
	 */	


	/* re-assigns standard output to go to the file referenced by fd
	 * The dup() system call uses the lowest-numbered, unused descriptor for the new one. 	
	 */

	if (dup(fd) < 0)
	{
		perror("ERROR: dup failed!");
		return -1;
	}

	printf("dup: This should be in the file and not on the screen\n");

	//clean up
	close(fd);	
}
