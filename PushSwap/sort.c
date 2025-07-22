/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:04:43 by ksan              #+#    #+#             */
/*   Updated: 2025/07/20 13:04:43 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_biggest_idx(t_list *llist)
{
	int	biggest;

	biggest = 0;
	while (llist)
	{
		if (llist->index > biggest)
			biggest = llist->index;
		llist = llist->next;
	}
	return (biggest);
}
static int	index_node_num(t_list *llist, int idx)
{
	int	node_num;

	node_num = 0;
	while (llist)
	{
		if (llist->index == idx)
			return (node_num);
		else
			node_num++;
		llist = llist->next;
	}
	return (node_num);
}

static void	chunk_sort(t_list **llist_a, t_list **llist_b, int chunk)
{
	int	i;

	i = 0;
	while (*llist_a)
	{
		if ((*llist_a)->index <= i)
		{
			ft_pb(llist_a, llist_b);
			ft_rb(llist_b, 0);
			i++;
		}
		else if ((*llist_a)->index <= i + chunk)
		{

			ft_pb(llist_a, llist_b);
			i++;
		}
		else
			ft_ra(llist_a, 0);

	}
}

static	void	final_sort(t_list **llist_a, t_list **llist_b)
{
	int	size;
	int	node_num;

	while (*llist_b)
	{
		node_num = index_node_num(*llist_b, get_biggest_idx(*llist_b));
		size = ft_lstsize(*llist_b);
		if (node_num <= size / 2)
		{
			while (node_num-- > 0)
				ft_rb(llist_b, 0);
		}
		else
		{
			while (node_num++ < size)
				ft_rrb(llist_b, 0);
		}
		ft_pa(llist_b, llist_a);
	}
}

void	sort(t_list **llist_a, t_list **llist_b)
{
	int	size_a;
	int	chunk;

	size_a = ft_lstsize(*llist_a);
	chunk = size_a / CHUNK_SIZE;

	chunk_sort(llist_a, llist_b, chunk);
	final_sort(llist_a, llist_b);
}

