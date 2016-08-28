#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SMSIZE 100

int share_mem_write(char *buff);
int share_mem_read(char *buff);
int reverse_str(char *str, int len);

int main()
{

	int fd[2];
	pid_t pid;

	char buff[255];
	int len;

	//create pipe
	pipe(fd);
	
	//create a child
	pid = fork();

	//child forking
	if (-1 == pid)
	{ 
		// indicates the fork was unsuccessful
		perror("cannot fork\n");
		exit(1);
	}	
	else if (0 == pid)
	{
		//child
		
		//close unwanted end
		close(fd[1]);
				
		//read the data from fd
		read(fd[0], &len, sizeof(len));
		read(fd[0], buff, len);	
		printf("\nString: %s\n", buff);
		
		//reverse string
		reverse_str(buff, strlen(buff));
		printf("Reversed String: %s\n", buff);
	
		//write reversed string to shared memory
		share_mem_write(buff);	
	}
	else
	{
		//parent
		
		//enter the string that you want to save
		printf("Enter the string: ");
		fgets(buff, 255, stdin);

		//strcpy(buff, "Hello");		
		len = strlen(buff);
		len++; //to account for null

		//close unwanted fd
		close(fd[0]);

		//write the data into this fd
		write(fd[1], &len, sizeof(len));
		write(fd[1], buff, len);
		
		sleep(5);

		//read from shared memory
		share_mem_read(buff);
		printf("String: %s\n", buff);
	}	
}

int share_mem_write(char *buff)
{
	int shmid, i, len;
	char *shm, *shm1;
	key_t key;

	//key 
	key = 'A';

	//create shared memory
	shmid = shmget(key, SMSIZE, IPC_CREAT | 0666);

	//check if created
	if(shmid < 0)
	{
		perror("shmget");
		exit(1);
	}	
	else
	{
		shm = shmat(shmid, NULL, 0);
		shm1 = shm;
		
		len = strlen(buff);
		
		//write to shared memory
		for(i = 0; i <= len; i++)
		{
			*shm1 = *buff;
			shm1++;
			buff++;
		}		
	}
	printf("value from shared memory: %s\n", shm);
	return 0;
	
}

int share_mem_read(char *buff)
{
	int shmid, i, len;
	char *shm, *shm1;
	key_t key;

	//key 
	key = 'A';

	//create shared memory
	shmid = shmget(key, SMSIZE, 0666);

	//check if created
	if(shmid < 0)
	{
		perror("shmget");
		exit(1);
	}	
	
	shm = shmat(shmid, NULL, 0);
	if(shm < 0)
	{
		perror("shmat");
		exit(0);
	}
	else
	{	
		printf("value from shared memory: %s\n", shm);
		shm1 = shm;
		len = strlen(buff);
		
		//read from shared memory
		for(i = 0; i <= len; i++)
		{
			*buff = *shm1;
			shm1++;
			buff++;
		}		
	}
	return 0;
}

int reverse_str(char *str, int len)
{
	int i;
	char string[10];
	char *str1 = string;

	for(i = 0; i <= len-1; i++)
	{
		str1[i] = str[len - 1 - i];
	}

	for(i = 0; i <= len-1; i++)
	{
		str[i] = str1[i];
	}
	str[i] = '\0';
}
