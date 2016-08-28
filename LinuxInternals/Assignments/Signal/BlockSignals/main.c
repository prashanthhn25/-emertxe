/*
 *	Assignment 3 block_signal.c
 *	WAP to block certain signals from being received from command-line 
 *	
 *	Pre-requisites:-  
 *	• Knowledge about system calls, How to read and understand ‘man pages’. 
 *	• Good knowledge about signals and signal handling. 
 *	• Working of sigaction system call and signal masking. 
 *
 *	Objective: 
 *	• To understand importance of signal masking. 
 *
 *	Requirements: 
 *	1. Write a signal handler function for any signal, say SIGINT . 
 *	2. While its running inside handler (use loop) block other signals(atleast 3) being received . 
 *	3. Use sa_mask from struct sigaction to set signals to be blocked (Refer man ). 
 *	4. To create a signal set use variable of sigset_t. 
 *	5. To add or remove signals from set use sigaddset, sigdelset functions (refer man). 
 *	6. Process will receive blocked signals once its out from handler.
 *
 *	Sample execution:
 *	1. ./block_signal Process 2345 waiting for signal.. 
 *	press ctrl + c from terminal. 
 *	SIGINT received  Inside handler  Inside handler . . .
 *	2. Now open another terminal and send signal to process using kill command. 
 *	Bash$ kill ­SIGUSR1 2345 
 *	Bash$ kill ­SIGTERM 2345 
 *	Bash$ kill ­SIGABRT 2345 
 *	3. After exiting from handler will respond to blocked signal.
 *
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handler(int signum, siginfo_t *info, void *dummy)
{
	int i = 20;
	printf("\n SIGINT recieved \n");
	while(i)
	{
		printf("Inside Handler...\n");
		i--;
		sleep(2);
	}

}

int main()
{

    	struct sigaction sa;

	sigset_t block_mask;

	memset(&sa,0,sizeof sa);
	sigemptyset (&block_mask);
  
	/* Block other terminal-generated signals while handler runs. */
	//user defined signal
	sigaddset(&block_mask, SIGUSR1);
	//aborted signal
  	sigaddset (&block_mask, SIGABRT);
	//terminated signal
  	sigaddset (&block_mask, SIGTERM);
  	
	sa.sa_mask = block_mask;
	
	sa.sa_sigaction = handler;	
 	sa.sa_flags = SA_SIGINFO ;
  
	printf("process %d waiting for signal\n", getpid());
	sigaction (SIGINT, &sa, 0);
	sleep(30);
}
