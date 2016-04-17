#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define FAILURE -1

typedef int data_t;
typedef struct snode
{
	data_t data;
	struct snode *link;
}SLink;

void print_list(SLink *);
int insert_at_first(SLink **, data_t);
int insert_at_last(SLink **, SLink **, data_t);
