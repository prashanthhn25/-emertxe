//race condition

#include <pthread.h>
#include <stdio.h>

int x = 0;

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

void * thread_func(void *arg)
{
	while(1)
	{
		//critical section lock and unlock using mutex
		pthread_mutex_lock(&mut);
		x = 5;
		x += 10;
		printf("%d \n", x);
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
