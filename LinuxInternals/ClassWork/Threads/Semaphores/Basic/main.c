#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>	

sem_t count;

void * fun(void * parm)
{
	int k = 5;
	int value;

	sem_wait(&count);
	
	//enter critical section
	sem_getvalue(&count, &value);
	printf("The semaphore count before loop: %d\n", value);
	
	while(k)
	{
		printf("Inside loop, value of k = %d\n", k);
		k--;
		sleep(1);
	}
	sem_post(&count);

	//exiting critical secyion
	sem_getvalue(&count, &value);
	printf("The semaphore count loop: %d\n", value);
}

int main()
{
	int i;
	pthread_t tid[2];

	sem_init(&count, 0, 3);
	
	//4. Binary semaphore acting as Mutex	
	//sem_init(&count, 0, 1);


	for(i = 0; i < 2; i++)
	{
		pthread_create(&tid[i], NULL, &fun, NULL);
	}

	for(i = 0; i < 2; i++)
	{
		pthread_join(tid[i], NULL);
	}

	//TODO:
	//1. change the value of loop index [i] to 5 and see change in print pattern
	//2. change the semaphore initial value to 5 and see change in print pattern
	//3. change the semaphore initial value to 2 and see change in print pattern
	//4. change the semaphore initial value to 1 {Binary Mutex} and see change in print pattern
		
	return 0;	
}
