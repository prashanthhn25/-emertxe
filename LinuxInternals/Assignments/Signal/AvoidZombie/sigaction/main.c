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

//METHOD 2 : catch using sigaction 
void handler_sigchld(int signum, siginfo_t *info, void *dummy)
{
	
	printf("Child %dterminated with exit code %d \n", info -> si_pid, info -> si_code);
	exit(1);
}

int main()
{
	pid_t pid;
	int status;

	/* it is implementation-defined whether SIGCHLD is raised in response to process termination
	 * when SA_NOCLDWAIT is set. Since you cannot rely on the handler function being invoked, 
	 * it follows that the handler cannot actually do anything if you want its behaviour to be portable.
	 */

	struct sigaction sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = handler_sigchld;
	
	sigemptyset(&sa.sa_mask);
	//SA_NOCLDSTOP flag prevents SIGCHLD from being raised when a child process stops or continues (as opposed to terminating)	
	//sa.sa_flags = SA_NOCLDSTOP;

	sa.sa_flags = SA_SIGINFO | SA_NOCLDSTOP | SA_NOCLDWAIT;

	if (sigaction(SIGCHLD, &sa, 0) == -1) 
	{
		perror(0);
  		exit(0);
	}


	pid = fork();

	if(pid < 0)
	{
		printf("Error: fork() failed");
		return 1;
	}
	else if (pid == 0)
	{

		//child process
		printf("child: %d\n", getpid());
		exit(0);
	}
	else
	{
		//parent process
		printf("parent: %d\n", getpid());
		sleep(2);
		exit(0);
	}
}
