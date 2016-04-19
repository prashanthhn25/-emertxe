#include "dlist.h"

int main()
{
	DLink *head = NULL;
	int result;
	
	insert_at_last(&head, 10);
	
	insert_at_last(&head, 20);
	insert_at_last(&head, 30);
	insert_at_last(&head, 40);
	print_list(head);

	insert_at_first(&head, 40);
	insert_at_first(&head, 30);
	print_list(head);

	delete_first(&head);
	print_list(head);

	delete_last(&head);
	print_list(head);

	delete_list(&head);
	print_list(head);
	
	
	insert_at_last(&head, 10);
	insert_at_last(&head, 20);
	insert_at_last(&head, 30);	
	print_list(head);

	result = delete_element(&head, 20);

	if ( result == NOELEMENT)
	{
		printf("No such element \n");	
	} 
	else if ( result == EMPTYLIST)
	{
		printf("List is Empty\n");	
	} 
	else if ( result == SUCCESS)
	{
		printf("Element deleted\n");	
	} 	

	print_list(head);

	return 0;
}
