/*
 *	Assignment 5 zomb_orph.c
 *	Create a scenario to make zombie process become orphan, 
 *	print status of each state. 
 *
 *	Pre-requisites:-  
 *	• Knowledge about system calls, How to read and understand ‘man pages’. 
 *	• Good knowledge about processes, zombie and orphan. 
 *	• Working of fork system call. Objective: 
 *	• To understand different states of a process. 
 *	
 *	Requirements: 
 *	1. Create a child process and print status that process is running 
 *	2. After some time print status that process is zombie state 
 *	3. After some time print zombie process cleared by init. 
 *	4. To print status use help of /proc/<pid>/status file. 
 *		For eg: if child pid is 1234, open file /proc/1234/status and print first 3 lines 5. 
 *		If that file is not available means that process is cleared.
 *
 *	
 *	Sample execution: 
 *	1. ./zomb_orph 
 *	A child created with pid 1234
 *	Name:  ./zomb_orph State: S (sleeping)
 *	Name:  /zomb_orph   (After some time) State: Z (zombie)
 *	Process 1234 cleared by init  (After some time)
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
	
	cpid =fork();

	if(cpid < 0)
	{
		printf("Error: fork() failed");
		return 1;
	}
	else if (cpid == 0)
	{
		//child process
		char buf[100];

		int pid = getpid();
		sprintf(buf, "cat /proc/%d/status | head -5", pid);
		printf("%s\n", buf);
		system(buf);
		
		//exit child process
		exit(1);
	}
	else
	{
		//parent process
		sleep(2);
		
		// to print status
		char buf[100];
		sprintf(buf, "cat /proc/%d/status | head -5", cpid);
		printf("%s\n", buf);
		system(buf);

		// to create second child
		int cpid2;
		cpid2 = fork();		

		if(cpid2 < 0)
		{
			printf("Error: fork() failed");
			return 1;
		}
		else if (cpid2 == 0)
		{
			//second child process
			sleep(2);
			
			//do confirm
			if(system(buf) != -1)
			{
				printf("process %d cleared by init", cpid);
		
			}
			else
			{
				printf("Error\n");
			}			
					
			
			//exit child two
			exit(1);
		}
		else
		{
			//parent process
			
			exit(1);
		}
	}
}
		

		
