#include "libc.h"

static void	swap_nodes(t_list **a, t_list **b, t_list **c)
{
	*a = *b;
	*c = *a;
}

t_list		*lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	int		first_iter;
	t_list	*current_node;
	t_list	*new_list_start;
	t_list	*new_list_end;
	t_list	*new_node;

	first_iter = 1;
	current_node = lst;
	new_list_start = NULL;
	new_list_end = NULL;
	while (current_node && (current_node != lst || first_iter) && f)
	{
		first_iter = 0;
		new_node = f(current_node);
		if (new_node == NULL)
			lstdel(&new_list_start, normal_delete);
		if (new_node == NULL)
			return (NULL);
		if (new_list_start == NULL)
			swap_nodes(&new_list_start, &new_node, &new_list_end);
		else
			lstaddend(&new_list_end, new_node);
		current_node = current_node->next;
	}
	return (new_list_start);
}
