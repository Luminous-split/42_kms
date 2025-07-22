/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_both.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 13:09:11 by ksan              #+#    #+#             */
/*   Updated: 2025/07/17 13:33:34 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_ss(t_list **llist_a, t_list **llist_b)
{
	ft_sa(llist_a, 1);
	ft_sb(llist_b, 1);
	ft_putstr_fd("ss\n", 1);
}

void	ft_rr(t_list **llist_a, t_list **llist_b)
{
	ft_ra(llist_a, 1);
	ft_rb(llist_b, 1);
	ft_putstr_fd("rr\n", 1);
}

void	ft_rrr(t_list **llist_a, t_list **llist_b)
{
	ft_rra(llist_a, 1);
	ft_rrb(llist_b, 1);
	ft_putstr_fd("rrr\n", 1);
}
