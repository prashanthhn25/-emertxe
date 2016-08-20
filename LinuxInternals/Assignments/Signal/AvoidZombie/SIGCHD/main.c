/*
 *	Assignment 4 avoid_zombie.c
 *	WAP to avoid a child become zombie by using signal handlers. 
 *	Implement it with two different method. 
 *	
 *	Pre-requisites:-  
 *	• Knowledge about system calls, How to read and understand ‘man pages’. 
 *	• Good knowledge about signals and signal handling. 
 *	• Working of sigaction system call. 
 *
 *	Objective:
 *	• To understand, how to avoid zombie asynchronously . 
 *
 *	Requirements: 
 *	Write two separate programs for both methods. 
 *
 *	Method 1 
 *	1. Create a child process. 
 *	2. Write a signal handler function for  SIGCHLD to avoid child become zombie       
 *		(Do man 7 signal for SIGCHLD) . 
 *	3. Write code inside handler to avoid zombie and print child exit status. 
 *
 *	Method 2 
 *	4. Create a child process. 
 *	5. Use sa_flag from struct sigaction to avoid zombie (Refer man ). 
 *	6. Prints the child exit status inside handler.
 *
 *	Sample execution: 
 *	1. ./avoid_zombie child <pid> terminated with exit code 0.
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/signal.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

//METHOD 1 : catch SIGCHLD 
void handler_sigchld(int status)
{
	pid_t pid;

	pid = wait(&status);
	printf("Child %d terminated with exit code %d \n", pid, WEXITSTATUS(status));
	
	exit(1);
}

int main()
{
	pid_t pid;
	int status;

	pid = fork();

	//to catch SIGCHLD
	signal(SIGCHLD, handler_sigchld); 

	if(pid < 0)
	{
		printf("Error: fork() failed");
		return 1;
	}
	else if (pid == 0)
	{
		//child process
		exit(0);
	}
	else
	{
		//parent process
		sleep(2);
		exit(0);
	}
}
