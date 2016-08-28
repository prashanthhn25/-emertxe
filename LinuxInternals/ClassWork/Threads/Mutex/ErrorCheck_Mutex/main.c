//race condition

#include <pthread.h>
#include <stdio.h>

int x = 0;

pthread_mutex_t mutex;

void fun(void)
{
	//critical section lock and unlock using mutex
	if( pthread_mutex_lock(&mutex) == 35) //EDEADLCK
	{
		printf("%lu already locked the mutex \n", pthread_self());
	}
	
}

void * thread_func(void *arg)
{
	printf("%lu locking mutex\n", pthread_self());
	pthread_mutex_lock(&mutex);
	printf("%lu locked mutex\n", pthread_self());
	fun();
	sleep(2);
	printf("%lu unlocking mutex\n", pthread_self());
	pthread_mutex_unlock(&mutex);
}

int main()
{
	pthread_t tid1;
	pthread_t tid2;
	
	//attribute variable
	pthread_mutexattr_t attr;

	//initialise attribute
	pthread_mutexattr_init(&attr);

	//set the type else it will be a normal fast mutex and will go into dead lock
	pthread_mutexattr_setkind_np(&attr, PTHREAD_MUTEX_ERRORCHECK);
	
	//initialize mutex with this attribute
	pthread_mutex_init(&mutex, &attr);

	pthread_create(&tid1, NULL, thread_func, NULL);	
	pthread_create(&tid2, NULL, thread_func, NULL);	

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	return 0;
}
