#include "dlist.h"

int delete_first(DLink **head)
{
	/* take a local reference of head */
	DLink *temp;
	temp = *head;

	/* check for if list is empty */
	if (NULL == (*head))
	{
		return EMPTYLIST;
	}

	/* check for if list has only one node */
	if ( ((*head) -> next) == NULL)
	{
		/* free the node, and update head with null */
		free(temp);
		(*head) = NULL;
		return SUCCESS;
	}
	else
	{
		/* if list has multiple nodes then, update head and free the first node */
		(*head) = ((*head) -> next);
		free(temp);
		return SUCCESS;
	}
	
	return FAILURE;
}
