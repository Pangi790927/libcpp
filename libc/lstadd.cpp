#include "libc.h"

void	lstadd(t_list **alst, t_list *new_node)
{
	if (new_node)
		new_node->next = (*alst);
	(*alst) = new_node;
}
