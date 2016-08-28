/*
 *	Assignment 7 exe_child.c
 *	WAP to create a child process which will execute command passed through commandline arguments.
 *	
 *	Pre-requisites:-  
 *	• Knowledge about system calls, How to read and understand ‘man pages’. 
 *	• Good knowledge about processes. • Working of fork, wait and exec system calls.
 *	
 *	Objective: 
 *	• To understand how to use exec system calls.
 *
 *	Requirements: 
 * 	1. Create child and execute a command passed from command-line arguments. 
 *	2. If no arguments passed print a usage message. 
 *	3. In case any wrong command passed, print an error message. 
 *	4. After child terminates print the exit status of child process.
 *	
 *	Sample execution: 
 *	1. No args passed (Print usage info)
 *	./exe_child Usage: ./exe_child args...
 *	2. Valid arg. passed
 *	./exe_child date This is the CHILD process, with id 11612 
 *	Wed Apr  4 13:27:19 IST 2012  
 *	Child exited with status 0
 *	3. Child terminated using SIGKILL (kill ­9)
 *	./exe_child sleep 20 & [1] 11617 
 *	$ This is the CHILD process, with id 11618
 *	$ kill ­9 11618 Child terminated abnormally Child exited with code 9
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	//check argument
	if (argc < 2)
	{
		printf(" No args passed (Print usage info)\n ./exe_child Usage:  ./exe_child args...\n");	
		return 0;
	}
	else
	{
		printf("Valid arg. passed\n");
		char *commandArray[argc];
		int i;

		for (i = 0; i < argc-1; i++)
		{
			commandArray[i] = argv[i+1];
		}
		commandArray[i] = NULL;
			
		//create child
		int cpid = fork();

		if(cpid < 0)
		{
			printf("Error: fork() failed");
			return 1;
		}
		else if (cpid == 0)
		{
			//child process
			int c_pid = getpid();

			printf("This is the CHILD process, with id %d\n", c_pid);
			//execute the command sent as argument
			if(execvp(argv[1], commandArray) < 0)
			{ 
				perror(commandArray[0]);
				exit(1);
			} 
			else
			{
				printf("execvp not executed\n");
			}
		}
		else
		{
			//parent process
			int status;
			int wpid = wait(&status);

			//check exit status of child
			if(WIFEXITED(status))
			{
				printf("Child exited with status %d \n", WEXITSTATUS(status));
			}
			else
			{
				printf("Child terminated abnormally \n");
				printf("Child exited with code %d \n", wpid, WEXITSTATUS(status));
			}
					
		exit(1);	
	
		}
	}	


}
