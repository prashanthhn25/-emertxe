/* finding factorial of a number by dividing that number to three threads */

#include <stdio.h>
#include <pthread.h>

/* create a structure */
struct fact_par
{
	int start;
	int end;
};

/*function program */
void *fact(void *parameter)
{
	/* structure and local variables declaration */
	struct fact_par *p = (struct fact_par *)parameter;
	unsigned long int value, factorial = 1;
	int i;

	/* checking the number is zero or not */
	if (p -> start == 0)
	{
		value = 1;
	}
	else
	{
		/* looping to find the factorial from start to end */
		for (i = p -> start; i <= p -> end; i++)
		{
			factorial = factorial * i;
		}
			value = factorial;
			
	}
	return (void *)value;

}

/* main program */
int main()
{
	/* local variables declaration */
	int n;
	unsigned long int p1, p2, p3;

	/* declaring threads */
	pthread_t thread_id1;
	pthread_t thread_id2;
	pthread_t thread_id3;

	struct fact_par thread_arg1;
	struct fact_par thread_arg2;
	struct fact_par thread_arg3;

	printf("\n enter the number\n");
	scanf("%d", &n);


	/* create a new thread */
	thread_arg1.start = 1;
	thread_arg1.end = n/3;
	
	/* create new thread. the new thread will run the print function */
	pthread_create (&thread_id1, NULL, &fact, &thread_arg1);
	
	/*create another new thread */
	thread_arg2.start = (n/3) + 1;
	thread_arg2.end = n - (n/3);
	
	pthread_create (&thread_id2, NULL, &fact, &thread_arg2);

	/*create another new thread */
	thread_arg3.start = n - (n/3) + 1;
	thread_arg3.end = n;
	
	pthread_create (&thread_id3, NULL, &fact, &thread_arg3);

	/* wait for thread to finish */
	pthread_join(thread_id1, (void **)&p1);
	pthread_join(thread_id2, (void **)&p2);
	pthread_join(thread_id3, (void **)&p3);
	printf("\nfactorial of p1 = %ld\n", p1);
	printf("\nfactorial of p2 = %ld\n", p2);
	printf("\nfactorial of p3 = %ld\n", p3);
	printf("\nfactorial = %ld\n", p1 * p2 * p3);
}

