/*
 *	Assignment 6 nonblock_wait.c
 *	WAP to avoid a child become zombie with out blocking the parent. 
 *	
 *	Pre-requisites:-  
 *	• Knowledge about system calls, How to read and understand ‘man pages’. 
 *	• Good knowledge about processes & zombie process. 
 *	• Working of fork & wait system call.
 *	
 *	Objective: 
 *	• To understand different states of a process.
 *	
 *	Requirements: 
 *	1. Create a child process avoid it become a zombie. 
 *	2. To avoid zombie we need to call wait(), but this block parent until child terminates. 
 *	3. So we need to use waitpid() with proper arguments (Read man page). 
 *	4. When child is working parent has to continuously print some message. 
 *	5. When ever child terminates parent has to print child terminated and print exit status of child process.
 *	
 *	Sample execution: 
 *	1. ./nonblock_wait
 *	A child created with pid 1234
 *	parent is running parent is running parent is running . . 
 *	Child 1234 terminated normally with exit status 0 parent terminating
 */

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>

int main()
{
	int cpid;
	int status;

	cpid =fork();

	if(cpid < 0)
	{
		printf("Error: fork() failed");
		return 1;
	}
	else if (cpid == 0)
	{
		//child process
		//exit child process
		sleep(5);
		exit(3);
		
	}
	else
	{
		//parent process
		int wpid;
		do
		{
			/* If WNOHANG was specified in options and there were no children in a waitable state,
			 * then waitid() returns 0 immediately and the state of the siginfo_t structure pointed 
			 * to by infop is unspecified.  To distinguish this case from that where a child was  in 
			 * a  waitable state, zero out the si_pid field before the call and
			 * check for a nonzero value in this field after the call returns.
			 */
			// check if child is exited or terminated
			wpid = waitpid(cpid, &status, WNOHANG);
			if(wpid == 0)
			{
				printf("parent is running...\n");
			}
			sleep(1);
			
		}while(wpid == 0);	

		//check exit status of child
		if(WIFEXITED(status))
		{
			printf("Child %d terminated normally with exit status %d \n", cpid, WEXITSTATUS(status));
		}
		exit(1);
	}
	return 0;
}
