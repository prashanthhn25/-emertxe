#include <stdio.h>
#include <unistd.h>
#include <sys/signal.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

//sigaction : catch SIGSEGV 
void handler(int signum, siginfo_t *info, void *dummy)
{
	printf("\nSignal recieved with %d \n", signum);
	printf("Signal send from %d\n", info -> si_pid);
	printf("Address %p\n", info -> si_addr);
	exit(1);
}
	

int main()
{
	int *ptr = (int *)0xABCD;
	int pid = getpid();

	struct sigaction act, oldact;
		
	memset(&act, 0, sizeof(act));
	act.sa_sigaction = handler;
	act.sa_flags = SA_SIGINFO | SA_RESETHAND;

	
	printf("id of the process %d\n", pid);

	sigaction(SIGSEGV, &act, &oldact);
	//to cause the error	
	*ptr = 10;

	//comment previous line and uncomment below line and run 
	//use kill -SIGSEGV pid in command line when run as ./a.out &	
	//pause(); 
	return 0;

}
