#include <pthread.h>

void * thread_function(void * thread_arg)
{
	//do work here
}

int main()
{	
	//create variable
	pthread_attr_t attr;
	pthread_t thread;

	//initialize
	pthread_attr_init(&attr);

	//change the attribute			
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	
	//create a thread with this state
	pthread_create(&thread, &attr, &thread_function, NULL);
	
	//destroy
	pthread_attr_destroy(&attr);

	/* do work here
  	 * No need to join the second thread 
	 */

	return 0;
}
