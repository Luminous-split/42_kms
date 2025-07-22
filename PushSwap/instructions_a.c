/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_a.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 13:09:11 by ksan              #+#    #+#             */
/*   Updated: 2025/07/17 15:55:17 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_sa(t_list **llist_a, int in_ss)
{
	t_list	*temp;
	t_list	*temp1;

	if (ft_lstsize(*llist_a) < 2)
		return ;
	temp = *llist_a;
	temp1 = (*llist_a)->next;
	*llist_a = (*llist_a)->next->next;
	add_front(llist_a, temp);
	add_front(llist_a, temp1);
	if (!in_ss)
		ft_putstr_fd("sa\n", 1);
}

void	ft_ra(t_list **llist_a, int in_rr)
{
	t_list	*first_node;
	t_list	*second_node;
	t_list	*last_node;

	if (!(*llist_a)->next)
		return ;
	first_node = *llist_a;
	second_node =  (*llist_a)->next;
	last_node = second_node;
	while (last_node->next)
		last_node = last_node->next;
	last_node->next = first_node;
	first_node->next = NULL;
	*llist_a = second_node;
	if (!in_rr)
		ft_putstr_fd("ra\n", 1);
}

void	ft_rra(t_list **llist_a, int in_rrr)
{
	t_list	*last_node;
	t_list	*second_last_node;

	if (!(*llist_a) || !(*llist_a)->next)
		return ;
	last_node = *llist_a;
	while (last_node->next)
	{
		second_last_node = last_node;
		last_node = last_node->next;
	}
	second_last_node->next = NULL;
	last_node->next = *llist_a;
	*llist_a = last_node;
	if (!in_rrr)
		ft_putstr_fd("rra\n", 1);
}

void	ft_pa(t_list **llist_b, t_list **llist_a)
{
	t_list	*first_node;

	if (!(*llist_b))
		return ;
	first_node = *llist_b;
	*llist_b = (*llist_b)->next;
	if (llist_a)
		add_front(llist_a, first_node);
	else
		*llist_a = first_node;
	ft_putstr_fd("pa\n", 1);
}


