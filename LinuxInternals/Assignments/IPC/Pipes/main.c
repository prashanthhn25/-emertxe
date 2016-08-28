/*
 *	Assignment 1 pipe.c
 *	WAP to create two child process which will execute command (with or without options) 
 *	passed through command-line arguments. First child will pass output to second child as input. 
 *	
 *	Pre-requisites:-  
 *	• Knowledge about system calls, How to read and understand ‘man pages’. 
 *	• Good knowledge about processes and IPC. 
 *	• Working of pipe & dup system calls. 
 *
 *	Objective: 
 *	• To understand working of pipe between two process. 
 *
 *	Requirements: 
 *	1. Create two child process and execute commands passed from command-line arguments 
 *	2. Each command is separated by a '|' (pipe) character. 
 *	3. First child execute first command (with or without options) and pass o/p to next. 
 *	4. Second child executes second command (after '|') will reads I/p from first cmd. 
 *	5. Parent will wait for both child process to finish .
 *	
 *	Sample execution: 
 *	1. ./pipe (No arguments) 
 *	Error: No arguments passed 
 *	Usage: ./pipe <command 1> | <command 2> 
 *	2. ./pipe ls  
 *	Error: Insufficient arguments passed 
 *	Usage: ./pipe <command 1> | <command 2> 
 *	3. ./pipe ls '|' wc 
 *	5 5 25 
 *	4. ./pipe ls ­l ­a '|' wc ­l ­w 
 *	10 15
 */

/*
 *	Assignment 2 three_pipes.c
 *	WAP to implement ls -l | grep “patern” | wc -l where pattern passed through commandline arguments.
 *	
 *	Pre-requisites:-  
 *	• Knowledge about system calls, How to read and understand ‘man pages’. 
 *	• Good knowledge about processes and IPC. • Working of pipe & dup system calls.
 *
 *	Objective: 
 *	• To understand working of multiple pipes between multiple process.
 *
 *	Requirements: 
 *	1. Create three child process and execute commands passed from command-line arguments 
 *	2. Each command is separated by a '|' (pipe) character. 
 *	3. First child execute first command (ls -l) and pass output to next command. 
 *	4. Second child executes second command (grep pattern) where pattern passed from command-line arguments.
 *	5. Third child executes wc -l
 *
 *	Sample execution: 
 *	1. ./three_pipes (No arguments) 
 *	Error: No arguments passed 
 *	Usage: ./three_pipes <command 1> | <command 2> 
 *	2. ./pipe ls ­l '|' grep  
 *	Error: Insufficient arguments passed 
 *	Usage: ./pipe <command 1> | <command 2> 
 *	3. ./pipe ls ­l '|' grep “pattern” | wc ­l 
 *	5 5 25
 */	

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int pipeCount = 0;
int twoPipe(char *command1Array[], char *command2Array[], char *command3Array[]);
int singlePipe(char *command1Array[], char *command2Array[]);
void parse(int argc, char *argv[], char *command1Array[], char *command2Array[], char *command3Array[]);

int main(int argc, char **argv)
{
	int i;
	char *command1Array[255];
	char *command2Array[255];
	char *command3Array[255];

	//check arg count
	if(argc == 1)
	{
		printf("Error: No arguments passed\nUsage: ./pipe <command 1> | <command 2>\n");
		return -1;
	}
	if(argc == 2)
	{
		printf("Error: Insufficient arguments passed\nUsage: ./pipe <command 1> | <command 2>\n");
		return -1;
	}
	else
	{
		//parse for commands
		parse(argc, argv, command1Array, command2Array, command3Array);	
		//printf("1: %s %s \n", command1Array[0], command1Array[1]);	
		//printf("2: %s %s \n", command2Array[0], command2Array[1]);
		//printf("3: %s %s \n", command3Array[0], command3Array[1]);
	}	

	//pipe execution
	if(pipeCount == 1)
	{
		//do code for singlePipe
		singlePipe(command1Array, command2Array);
	}
	else if(pipeCount == 2)
	{
		//do code for twoPipe	
		twoPipe(command1Array, command2Array, command3Array);
	}
	else
	{
		printf("Error: Too many pipes\n");
		return -1;
	}
	
}


int twoPipe(char *command1Array[], char *command2Array[], char *command3Array[])
{
	int pipe1fd[2];
	int pipe2fd[2];
	
	pid_t firstChildPid;
	pid_t secondChildPid;
	pid_t thirdChildPid;

	//create first pipe
	pipe(pipe1fd);

	//firstchild forking
	if (-1 == (firstChildPid = fork()))
	{ 
		//first child
		// indicates the fork was unsuccessful
		perror("cannot fork\n");
		exit(1);
	}
	else if (0 == firstChildPid)
	{
		// first of two child processes 
		// redirect to parent [stdout]
		if (dup2(pipe1fd[1],1) < 0)
		{
			perror("ERROR: dup2 failed!");
			exit(2);
		}

		// close the file descriptor 
		close(pipe1fd[0]);
		close(pipe1fd[1]);

		//execute the command
		if(execvp(command1Array[0], command1Array)<0)
		{ 
			perror(command1Array[0]);
			exit(3);
		}
	}

	//open the second pipe
	pipe(pipe2fd);

	//secondChildPid = fork();	
	if (-1 == (secondChildPid = fork()))
	{ 
		//second child
		// indicates the fork was unsuccessful
		perror("cannot fork\n");
		exit(4);
	}
	else if (0 == secondChildPid)
	{
		//close unwanted fd of pipe 1
		close(pipe1fd[1]);
		
		// second of three child processes 
		// redirect output from previous child to input [stdin] 
		if (dup2(pipe1fd[0],0)<0)
		{
			perror("ERROR: dup2 failed!");
			exit(5);
		}

		// close the file descriptor 
		close(pipe1fd[0]);

		//close unwanted fd of pipe2
		close(pipe2fd[0]);

		//redirect from input to pipe2
		if (dup2(pipe2fd[1],1)<0)
		{
			perror("ERROR: dup2 failed!");
			exit(5);
		}

		// close the file descriptor 
		close(pipe2fd[1]);

		//execute the command
		if(execvp(command2Array[0], command2Array)<0)
		{ 
			perror(command2Array[0]);
			exit(3);
		}
	
	}
	
	// close the file descriptor for pipe1
	close(pipe1fd[0]);
	close(pipe1fd[1]);
	
	//thirdChildPid = fork();	
	if (-1 == (thirdChildPid = fork()))
	{ 
		//third child
		// indicates the fork was unsuccessful
		perror("cannot fork\n");
		exit(4);
	}
	else if (0 == thirdChildPid)
	{
		//close unwanted end of pipe 2
		close(pipe2fd[1]);
		
		// third of three child processes 
		// redirect output from previous child to input [stdin] 
		if (dup2(pipe2fd[0],0)<0)
		{
			perror("ERROR: dup2 failed!");
			exit(5);
		}

		// close the file descriptor 
		close(pipe2fd[0]);
		
		//execute the command
		if(execvp(command3Array[0], command3Array)<0)
		{ 
			perror(command3Array[0]);
			exit(3);
		}
				
	}

	// close the file descriptor 
	close(pipe2fd[0]);
	close(pipe2fd[1]);
	

	// wait() might find the first child; continue reaping children until the second child is found 
	for(;;)
	{
		pid_t pid;
		pid = wait(NULL);
		if(pid == secondChildPid)
		{
			break;
		}
		if(pid == firstChildPid)
		{
			break;
		}
		if(pid == thirdChildPid)
		{
			break;
		}
	}

}

int singlePipe(char *command1Array[], char *command2Array[])
{
	int pipefd[2];
	pid_t firstChildPid;
	pid_t secondChildPid;

	//pipe
	pipe(pipefd);

	//firstchild forking
	if (-1 == (firstChildPid = fork()))
	{ 
		//first child
		// indicates the fork was unsuccessful
		perror("cannot fork\n");
		exit(1);
	}
	else if (0 == firstChildPid)
	{
		// first of two child processes 

		
		// redirect to parent [stdout]
		if (dup2(pipefd[1],1) < 0)
		{
			perror("ERROR: dup2 failed!");
			exit(2);
		}

		// close the file descriptor 
		close(pipefd[1]);
		//close unwanted end of pipe
		close(pipefd[0]);
		
		//execute the command
		if(execvp(command1Array[0], command1Array)<0)
		{ 
			perror(command1Array[0]);
			exit(3);
		}
	}
	
	//secondChildPid = fork();	
	if (-1 == (secondChildPid = fork()))
	{ 
		//second child
		// indicates the fork was unsuccessful
		perror("cannot fork\n");
		exit(4);
	}
	else if (0 == secondChildPid)
	{
		// second of two child processes 

		
		// redirect output from previous child to input [stdin] 
		if (dup2(pipefd[0],0)<0)
		{
			perror("ERROR: dup2 failed!");
			exit(5);
		}

		// close the file descriptor 
		close(pipefd[0]);
		//close unwanted end of the pipe
		close(pipefd[1]);


		//execute the command
		if(execvp(command2Array[0], command2Array)<0)
		{ 
			perror(command2Array[0]);
			exit(3);
		}
		
		
	}
	
	// close the file descriptor 
	close(pipefd[0]);
	close(pipefd[1]);
	

	// wait() might find the first child; continue reaping children until the second child is found 
	for(;;)
	{
		pid_t pid;
		pid = wait(NULL);
		if(pid == secondChildPid)
		{
			break;
		}
		if(pid == firstChildPid)
		{
			break;
		}
	}
}

void parse(int argc, char *argv[], char *command1Array[], char *command2Array[], char *command3Array[])
{
	int i, count1 = 0, count2 = 0, count3 = 0;
		
	for (i = 1; i < argc; i++)
	{
		//check for '|'
		if( strcmp(argv[i], "|") != 0)
		{
			if(pipeCount == 0)
			{
				//save only the commands
				command1Array[count1++] = argv[i];
			}
			else if(pipeCount == 1)
			{
				//save only the commands
				command2Array[count2++] = argv[i];
			} 
			else if(pipeCount == 2)
			{
				//save only the commands
				command3Array[count3++] = argv[i];
			} 
			
		}
		else
		{
			//get the pipe count
			pipeCount++;			
			continue;
		}
	}
	command1Array[count1] = NULL;
	command2Array[count2] = NULL;	
	command3Array[count3] = NULL;	
}
