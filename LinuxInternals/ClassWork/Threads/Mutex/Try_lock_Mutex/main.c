//try lock condition

#include <pthread.h>
#include <stdio.h>
#include <errno.h>

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

void * thread_func(void *arg)
{
	if(pthread_mutex_trylock(&mut) == EBUSY)
	{
		printf("%lu Mutex already locked\n", pthread_self());
	}
	else
	{
		printf("Mutex was ffree...So %lu taken \n", pthread_self());
		sleep(5);
		
		pthread_mutex_unlock(&mut);
	}
}

int main()
{
	pthread_t tid1;
	pthread_t tid2;

	pthread_create(&tid1, NULL, thread_func, NULL);	
	pthread_create(&tid2, NULL, thread_func, NULL);	

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	return 0;
}
