/*
 *	Assignment 8 three_child.c
 *	WAP to create three child processes from same parent.
 *	
 *	Pre-requisites:-  
 *	• Knowledge about system calls, How to read and understand ‘man pages’. 
 *	• Good knowledge about processes. • Working of fork & wait system calls.
 *	
 *	Objective: 
 *	• To understand how to use fork system calls.
 *	
 *	Requirements: 
 *	1. Create three child process from same parent. 
 *	2. Parent has to wait for all three child process. 
 *	3. Print exit status of each child when they terminates.
 *
 *	Sample execution: 
 *	1. ./three_child 
 *	Child 1 with pid 2020 created 
 *	Child 2 with pid 2021 created 
 *	Child 3 with pid 2022 created 
 *	Child 2020 is terminated with code 0 
 *	Child 2021 is terminated with code 0 
 *	Child 2022 is terminated with code 0
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

	//create child1
	int cpid1 = fork();
	
	if(cpid1 < 0)
	{
		printf("Error: fork() failed");
		return 1;
	}
	else if (cpid1 == 0)
	{
		//child1 process
		printf("Child 1 with pid %d created\n", getpid());
		
		//exit 
		exit(0);
	}
	else
	{
		//parent process
		
		
		//create child2
		int cpid2 = fork();
	
		if(cpid2 < 0)
		{
			printf("Error: fork() failed");
			return 1;
		}
		else if (cpid2 == 0)
		{
			//child1 process
			printf("Child 2 with pid %d created\n", getpid());
			
			//exit 
			exit(0);
		}
		else
		{
			//create child3
			int cpid3 = fork();
	
			if(cpid3 < 0)
			{
				printf("Error: fork() failed");
				return 1;
			}
			else if (cpid3 == 0)
			{
				//child1 process
				printf("Child 3 with pid %d created\n", getpid());
				
				//exit 
				exit(0);
			}
			else
			{
				//parent process
				int status;
				int wpid;
				int i = 0;
				sleep(1);
			
				for(i = 0; i < 3; i++)
				{
					//wait for children
					wpid = wait(&status);
					
					//check exit status of child
					if(WIFEXITED(status))
					{
						printf("Child %d exited with status %d \n", wpid, WEXITSTATUS(status));
					}
				}
				
						
			}			
		}	
	}
	return 0;
}

