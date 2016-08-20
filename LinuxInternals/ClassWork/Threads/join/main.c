//passing 4th arg

#include <stdio.h>
#include <pthread.h>

/* create a structure */
struct char_print
{
	char character;
	int count;
};

void *char_print(void *parameter)
{
	struct char_print *p = (struct char_print *)parameter;
	int i;

	for (i = 0; i < p -> count; ++i)
		fputc(p -> character, stderr);
		return NULL;

}

int main()
{
	pthread_t thread_id1;
	pthread_t thread_id2;

	struct char_print thread_arg1;
	struct char_print thread_arg2;

	/* create a new thread */
	thread_arg1.character = 'x';
	thread_arg1.count = 300000;
	
	/* create new thread. the new thread will run the print function */
	pthread_create (&thread_id1, NULL, &char_print, &thread_arg1);
	
	/*create another new thread */
	thread_arg2.character = 'o';
	thread_arg2.count = 200000;
	
	pthread_create (&thread_id2, NULL, &char_print, &thread_arg2);

	/* wait for thread to finish */
	pthread_join(thread_id1, NULL);
	pthread_join(thread_id2, NULL);
}

