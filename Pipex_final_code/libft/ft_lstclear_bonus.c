/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:22:23 by ksan              #+#    #+#             */
/*   Updated: 2025/05/19 12:22:23 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *));

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp_container;
	t_list	*templst;

	if (!lst || !del)
		return ;
	templst = *lst;
	while (templst)
	{
		temp_container = templst->next;
		del(templst->content);
		free(templst);
		templst = temp_container;
	}
	*lst = NULL;
}
