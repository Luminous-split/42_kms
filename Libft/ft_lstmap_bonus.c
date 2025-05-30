/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:50:43 by ksan              #+#    #+#             */
/*   Updated: 2025/05/19 12:50:43 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*finallst;
	t_list	*newnode;
	void	*newcontent;

	if (!lst || !f)
		return (NULL);
	finallst = NULL;
	newnode = NULL;
	while (lst)
	{
		newcontent = f(lst->content);
		newnode = ft_lstnew(newcontent);
		if (!newnode)
		{
			free(newcontent);
			ft_lstclear(&finallst, del);
			return (NULL);
		}
		ft_lstadd_back(&finallst, newnode);
		lst = lst->next;
	}
	return (finallst);
}
