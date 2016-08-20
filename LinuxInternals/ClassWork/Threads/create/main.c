//thread create

#include <stdio.h>
#include <pthread.h>

void *print(void *unused)
{
	while (1)
	{
		fputc('x', stderr);
	}
}

int main()
{
	pthread_t thread_id;
	
	/* create new thread. the new thread will run the print function */
	pthread_create (&thread_id, NULL, &print, NULL);
	
	while (1)
	{
		fputc('o', stderr);
	}
}

