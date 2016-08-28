//pipe : IPC

#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main()
{

	int fds[2];
	pid_t pid;
	
	//create a pipe here, before fork
	pipe(fds);

	pid = fork();
	if(pid == 0)
	{
		int num, str_len;
		char buf[20];

		printf("Inside child process...\n");
		printf("Enter the integer you want to share with parent\n");
		scanf("%d", &num);

		//to scan the string
		printf("Enter the string you want to share with parent\n");
		scanf("%s", buf);
		str_len = strlen(buf);

		close(fds[0]);
		
		//write into pipe for the parent to read
		write(fds[1], &num, sizeof(num));

		//exchange a string between parent and chold by sending the length first
		write(fds[1], &str_len, sizeof(str_len));
		write(fds[1], &buf, sizeof(buf));
	
	}
	else
	{
		int num, str_len;
		char buf[20];
	
		printf("Inside parent process...\n");
		close(fds[1]);

		//read from the pipe and print the output
		read(fds[0], &num, sizeof(num));
		printf("integer received from parent: %d\n", num);

		//read from the pipe and print string
		read(fds[0], &str_len, sizeof(str_len));
		read(fds[0], &buf, sizeof(str_len));
		printf("string received from parent: %s\n", buf);
	
	}

	return 0;
}
