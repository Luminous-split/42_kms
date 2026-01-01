/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:04:44 by ksan              #+#    #+#             */
/*   Updated: 2025/05/19 11:04:44 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst);

int	ft_lstsize(t_list *lst)
{
	t_list	*templst;
	int		size;

	if (!lst)
		return (0);
	size = 0;
	templst = lst;
	while (templst->next != NULL)
	{
		size++;
		templst = templst->next;
	}
	return (size + 1);
}
