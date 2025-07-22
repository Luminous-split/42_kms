
#include "push_swap.h"

void	index_nodes(t_list *llist)
{
	t_list *temp;
	t_list *smaller_node;
	int	smaller_num;
	int	size = ft_lstsize(llist);
	int	i;

	i = -1;
	while (++i < size)
	{
		temp = llist;
		smaller_num = INT_MAX;
		smaller_node = NULL;
		while (temp)
		{	if (temp->index == -1 && *(temp->num) < smaller_num)
			{
				smaller_num = *(temp->num);
				smaller_node = temp;
			}
			temp = temp->next;
		}
		if (smaller_node)
			smaller_node->index = i;
	}
}
