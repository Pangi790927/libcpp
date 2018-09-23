#include "libc.h"

void	dlist_swap(t_dlist *first, t_dlist *second)
{
	if (first == NULL || second == NULL)
		return ;
	first->next->prev = second;
	first->prev->next = second;
	second->prev->next = first;
	second->next->prev = first;
	dlist_ptr_swap(&(first->next), &(second->next));
	dlist_ptr_swap(&(first->prev), &(second->prev));
}
