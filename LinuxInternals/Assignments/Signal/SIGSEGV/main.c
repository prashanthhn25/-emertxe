/*
 *	Assignment 1 sigsegv.c
 *	WAP to print the address which causing segmentation fault. 
 *
 *	Pre-requisites:-  
 *	• Knowledge about system calls, How to read and understand ‘man pages’. 
 *	• Good knowledge about signals and signal handling. 
 *	• Working of sigaction system calls. Objective: 
 *	• To understand working of signal handling. 
 *	
 *	Requirements: 
 *	1. Write a signal handler function  to print address which caused seg-fault(SIGSEGV). 
 *	2. Use sigaction system call to register signal. 
 *	3. Use struct siginfo from sa_sigaction to print address (Read man page). 
 *	4. Create a segmentation fault from code.  
 *	5. When error occurs program should print address and exit.
 *
 *	Sample execution: 
 *	1. ./sigsegv 
 *	Segmentation fault ..!!
 *	Address 0x123456 caused error
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/signal.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

//sigaction 
void handler(int signum, siginfo_t *info, void *dummy)
{
	printf("Segmentation fault ..!!\n");
	printf("Address %p caused error\n", info -> si_addr);
	exit(1);
}
	

int main()
{
	int *ptr = (int *)0xABCD;
	
	struct sigaction act, oldact;
	
	//prerequists for using sigaction
	memset(&act, 0, sizeof(act));
	act.sa_sigaction = handler;
	act.sa_flags = SA_SIGINFO | SA_RESETHAND;
	
	//sigaction to catch SIGSEGV signal
	sigaction(SIGSEGV, &act, &oldact);
	//to cause the error	
	*ptr = 10;

	return 0;

}
