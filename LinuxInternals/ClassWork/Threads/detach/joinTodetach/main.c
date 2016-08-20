//join to detached thread 
#include <pthread.h>

void * thread_function(void * thread_arg)
{
	//do work here
	pthread_detach(pthread_self());
}

int main()
{	
	pthread_t thread_id;
	
	/* create new thread. the new thread will run the print function */
	//the thread_function will become independent and will not return anything,
	
	pthread_create (&thread_id, NULL, &thread_function, NULL);
	
	//we can force cancel the detached thread, 
	//pthread_cancel(...);

	return 0;
}
