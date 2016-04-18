#include "slist.h"

int delete_element(SLink **head, SLink **tail, data_t data)
{
	/* take a local reference of head */
	SLink *temp, *temp2;
	temp = *head;

	/* check for if list is empty */
	if (NULL == (*head))
	{
		return EMPTYLIST;
	}
	
	/* check for if list has only one node */
	if ((*head) == (*tail))
	{
		if (((*head) -> data) == data)
		{
			/* free the node, and update tail and head with null */
			free(temp);
			(*head) = NULL;
			(*tail) = NULL;
			return SUCCESS;
		}
		else
		{
			return NOELEMENT;
		}
	}
	else
	{
		/* If the element is in the head */
		if( ((*head) -> data) == data)
		{
			temp2 = (*head);
			(*head) = (*head) -> link;
			free(temp2);
		}
		else
		{
			/* if list has multiple nodes then, iterate till tail-1 node */
			while ( ((temp->link)-> data ) != data)
			{
				temp = temp -> link;
			}
	
			/* take a local reference to the element node */
			temp2 = temp -> link;

			/* update that node's link, free the next node that contains element */
			(temp -> link) = temp2 -> link;
			free(temp2);
		}
		return SUCCESS; 
	}	
	return FAILURE;
}
