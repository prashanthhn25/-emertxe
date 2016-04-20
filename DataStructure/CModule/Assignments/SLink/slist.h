#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define FAILURE -1
#define EMPTYLIST 1
#define NOELEMENT 2

typedef int data_t;
typedef struct snode
{
	data_t data;
	struct snode *link;
}SLink;

void print_list(SLink *);
int insert_at_first(SLink **, data_t);
int insert_at_last(SLink **, SLink **, data_t);
int delete_first(SLink **head, SLink **tail);
int delete_last(SLink **head, SLink **tail);
int delete_element(SLink **head, SLink **tail, data_t data);
int delete_list(SLink **head, SLink **tail);
int insert_after(SLink **head, data_t a_data, data_t n_data);
int insert_before(SLink **head, data_t b_data, data_t n_data);

