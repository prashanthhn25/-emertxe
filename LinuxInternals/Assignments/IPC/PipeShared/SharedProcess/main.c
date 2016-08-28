#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SMSIZE 100 //shared memory size

int main()
{
	int shmid, len, i;
	char *shm, *shm1, num;
	key_t key;

	key = 'A';

	shmid = shmget(key, SMSIZE, 0666);

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
		len = strlen(shm);

		//read from shared memory convert to upper case and write into shared memory
		for(i = 0; i < len; i++ )
		{
			if(islower(*shm1))
			{
				*shm1 = (*shm1 - 32);
			}
			shm1++;
		}
	}
	return 0;	
}
