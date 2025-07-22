/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_b.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 13:09:11 by ksan              #+#    #+#             */
/*   Updated: 2025/07/17 16:06:01 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_sb(t_list **llist_b, int in_ss)
{
	t_list	*temp;
	t_list	*temp1;

	if (ft_lstsize(*llist_b) < 2)
		return ;
	temp = *llist_b;
	temp1 = (*llist_b)->next;
	*llist_b = (*llist_b)->next->next;
	add_front(llist_b, temp);
	add_front(llist_b, temp1);
	if (!in_ss)
		ft_putstr_fd("sb\n", 1);
}

void	ft_rb(t_list **llist_b, int in_rr)
{
	t_list	*first_node;
	t_list	*second_node;
	t_list	*last_node;

	if (!(*llist_b)->next)
		return ;
	first_node = *llist_b;
	second_node =  (*llist_b)->next;
	last_node = second_node;
	while (last_node->next)
		last_node = last_node->next;
	last_node->next = first_node;
	first_node->next = NULL;
	*llist_b = second_node;
	if (!in_rr)
		ft_putstr_fd("rb\n", 1);
}

void	ft_rrb(t_list **llist_b, int in_rrr)
{
	t_list	*last_node;
	t_list	*second_last_node;

	if (!(*llist_b) || !(*llist_b)->next)
		return ;
	last_node = *llist_b;
	while (last_node->next)
	{
		second_last_node = last_node;
		last_node = last_node->next;
	}
	second_last_node->next = NULL;
	last_node->next = *llist_b;
	*llist_b = last_node;
	if (!in_rrr)
		ft_putstr_fd("rrb\n", 1);
}

void	ft_pb(t_list **llist_a, t_list **llist_b)
{
	t_list	*first_node;

	if (!(*llist_a))
		return ;
	first_node = *llist_a;
	*llist_a = (*llist_a)->next;
	if (llist_b)
		add_front(llist_b, first_node);
	else
		*llist_b = first_node;
	ft_putstr_fd("pb\n", 1);
}
