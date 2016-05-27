#include <stdio.h>
#include <signal.h>

static int count;
int flag = 0;
int alarmflag = 0;

//signal handler that needs to be exceuted upon catching the signal
void handler(int arg)
{
	if(arg == SIGINT)
	{
		//do minimal work in the handler and rest always in main using flags
		printf("Signal SIGINT receive %d \t", arg);
		flag = 1;
	}
	if(arg == SIGTSTP)
	{	
		printf("Signal SIGTSTP receive %d \n", arg);
	}
	if(arg == SIGALRM)
	{	
		printf("Signal SIGALRM receive %d \n", arg);
		//setting the alarmflag so we can make the SIGTSTP asignal to defaut
		alarmflag = 1;
	}
}
	

// to catch signlas : SIGSEGV on gdb ./a.out 
int main(int argc, char **argv)
{
	//to catch SIGSEGV 
	//printf("%d", *(int *) 0xABCD);

	//check for arg count
	if(argc != 2)
	{
		printf("Insufficient arguments\n");
		printf("Usage: ./a.out <alarm_time> \n");
		return 1;
	}
	
	//signal handling the process must be in running, only then signal can be caught
	signal(SIGTSTP, handler); //for ctrl+z
	
	signal(SIGINT, handler); //for ctrl+c

	signal(SIGALRM, handler); //for alarm
	alarm(atoi(argv[1])); //by default when SIGALRM is not caught, it gives Alarm clock and terminates after 5 sec

	while(1) 
	{
		//flag is used to do things when ctrl+c is caught and returned like here counted and is printed
		if(flag)
		{
			count++;
			printf("%d \n", count);
			flag = 0;
		}
		//if count if ctrl+c  is reached 6, we set signal to default behaviour
		if(count == 6)
		{
			signal(SIGINT, SIG_DFL);
		}
		sleep(1);

		//after 5 sec, treat SIGTSTP also as default
		if(alarmflag)
		{
			signal(SIGTSTP, SIG_DFL);
		}
	}
	return 0;
}
