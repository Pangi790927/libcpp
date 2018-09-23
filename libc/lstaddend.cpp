#include "libc.h"

void	lstaddend(t_list **end_node, t_list *new_node)
{
	if (*end_node)
		(*end_node)->next = new_node;
	(*end_node) = new_node;
}
