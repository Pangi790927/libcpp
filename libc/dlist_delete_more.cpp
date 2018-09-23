#include "libc.h"

void	dlist_delete_more(t_dlist **node, void (*del)(void *, size_t))
{
	t_dlist *next_node;

	if ((*node) == NULL)
		return ;
	next_node = (*node)->next;
	dlist_delete(node, del);
	dlist_delete_more(&next_node, del);
}
