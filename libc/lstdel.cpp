#include "libc.h"

void	lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*next_node;

	if (alst == NULL)
		return ;
	if ((*alst) == NULL)
		return ;
	next_node = (*alst)->next;
	lstdelone(alst, del);
	lstdel(&next_node, del);
}
