/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:58:00 by ksan              #+#    #+#             */
/*   Updated: 2025/05/19 10:58:00 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new);

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*templst;

	if (!lst || !new)
		return ;
	templst = *lst;
	if (*lst != NULL)
	{
		while (templst->next != NULL)
			templst = templst->next;
		templst->next = new;
	}
	else
		*lst = new;
}
