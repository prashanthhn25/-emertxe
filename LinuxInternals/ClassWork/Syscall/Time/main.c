
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/time.h>
#include <sys/mman.h>
#include <time.h>

#include <fcntl.h>
#include <sys/types.h>

int main()
{
	struct timeval tv;
	time_t my_time;
	struct tm only_time;

	gettimeofday(&tv, NULL);
	my_time = time(NULL);
	localtime_r(&my_time, &only_time);
	
	printf("%ld	%ld\n", tv.tv_sec, tv.tv_usec);
	printf("my_time %ld\n", my_time);
	printf("%s", ctime(&my_time));
	printf("Only time: %d:%d:%d\n", only_time.tm_hour, only_time.tm_min, only_time.tm_sec);
	return 0;
}

