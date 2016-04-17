#include "slist.h"

void print_list(SLink *head)
{
	SLink *temp = head;
	
	while(temp)
	{
		printf("%d ", temp -> data);
		temp = temp -> link;
	}
	printf("\n");
}
