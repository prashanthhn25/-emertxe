#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define BUFF_SIZE 255
#define SUCCESS 0
#define FAILURE -1

int my_copy(int source_fd, int dest_fd);
int word_count(int fd, int *lines, int *words, int *bytes);
