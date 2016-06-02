/*
 *	Assignment 4: fcntl_lock.c
 *	Write a program to understand advanced file control system calls.
 *
 *	Pre-requisites:-
 *	 Knowledge about system calls, How to read and understand ‘man pages’.
 *	 Command line arguments, File operation system calls (open, read, write, close ...etc)
 *	 Working of fcntl system calls.
 *
 *	Objective: -
 *	 To understand and implement using advanced system calls.
 *	 Understand the need of file synchronization between processes.
 *
 *	Requirements: -
 *	1. Using fcntl system call synchronize a file between two processes (parent and child process).
 *	2. Pass the file name using command-line arguments.
 *	3. Before writing to file check file is locked, in case it is locked must wait the process until its unlocked.
 *	4. If its unlocked, lock file and continue with writing.
 *	5. Both process will do the same procedure.	
 *
 *	NOTE:
 *	-> A read lock is placed on a readable file descriptor.
 *	-> A write lock is placed on a writable file descriptor.
 *	-> Only one process may hold a write lock.
 *	-> More than one process may hold a read lock on the same file at the same time.	
 *	-> The same file may not be both locked for read and locked for write.
 *	-> placing a lock does not actually prevent other processes from opening the file,
 *		 reading from it, or writing to it, unless they acquire locks with fcntl as well.
 *	 
 */

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char **argv)
{
	int fd; 
	struct flock lock;
	pid_t pid;
	int status;

	/* Do arg count check */
    	if (argc < 2)
    	{
        	printf("Insufficient arguments\n");
		printf("Usage:- ./my_fcntl_lock <file> \n");
        	return 1;
    	}	

	printf ("opening.....\n");
	/* open the file on which synchronization is performed */
	if ( (fd = open(argv[1], O_APPEND|O_WRONLY)) == -1 )
	{
		perror("open");
		return -1;	
	}

	/* Create a new process */
	pid = fork();
    	if(pid < 0)
	{
	        perror("fork");
	        return 1;
	}

	if(pid == 0)
	{
           	//pause();
           	/* I'm the child */
           	printf("Child's turn!\n");
		sleep(2);
		//if lock is present wait for release
		 if ( 0 == fcntl(fd, F_SETLK, &lock) )
		 {
			printf ("locked; hit Enter to unlock... ");
 			/* Wait for the user to hit Enter. */
 			getchar ();

			printf ("unlocking\n");
			/* Release the lock. */
 			lock.l_type = F_UNLCK;
			fcntl (fd, F_SETLKW, &lock);
		 }	
		 else
		{
			printf ("locking.....\n");
			/* Initialize the flock structure. */
 			memset (&lock, 0, sizeof(lock));
 			/* to set write lock */
			lock.l_type = F_WRLCK;
			/* Place a write lock on the file. */
 			fcntl (fd, F_SETLKW, &lock);

		}
          
		close (fd);	

	}
	else
	{
		/* I'm the parent */
	        printf("Parent's turn!\n");
		int wpid = waitpid(&status);
			
		//if lock is present wait for release
		 if ( 0 == fcntl(fd, F_SETLK, &lock) )
		 {
			printf ("locked; hit Enter to unlock... ");
 			/* Wait for the user to hit Enter. */
 			getchar ();

			printf ("unlocking\n");
			/* Release the lock. */
 			lock.l_type = F_UNLCK;
			fcntl (fd, F_SETLKW, &lock);
		 }	
		 else
		{
			printf ("locking.....\n");
			/* Initialize the flock structure. */
 			memset (&lock, 0, sizeof(lock));
 			/* to set write lock */
			lock.l_type = F_WRLCK;
			/* Place a write lock on the file. */
 			fcntl (fd, F_SETLKW, &lock);

			
		}
          
		close (fd);

	}		

	
	
 	return 0;
}
