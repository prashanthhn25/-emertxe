#include "slist.h"

int insert_at_last(SLink **head, SLink **tail, data_t data)
{
	SLink *new = malloc(sizeof(SLink));

	if (NULL == new)
	{
		return FAILURE;
	}

	/* update the data and link */
	new -> data = data;
	new -> link = NULL;

	/* If empty list */
	if ( (NULL == (*head)) && (NULL == (*tail)) )
	{
		/* update head and tail */
		(*head) = new;
		(*tail) = new;
	} 
	else
	{
		/* establish link between last + new Node and updte tail */
		((*tail) -> link) = new;
		(*tail) = new;
	}
	return SUCCESS;
}
