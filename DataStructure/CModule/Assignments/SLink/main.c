#include "slist.h"

int main()
{
	SLink *head = NULL;
	SLink *tail = NULL;

	insert_at_last(&head, &tail, 10);
	insert_at_last(&head, &tail, 20);
	insert_at_last(&head, &tail, 30);
	insert_at_last(&head, &tail, 40);

	print_list(head);

	insert_at_first(&head, 40);
	insert_at_first(&head, 30);
	
	print_list(head);

	return 0;
}
