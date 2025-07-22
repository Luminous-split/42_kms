/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:19:13 by ksan              #+#    #+#             */
/*   Updated: 2025/07/16 16:39:47 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_list	*lst_new(void *content);

int	ft_lstsize(t_list *llist);

void	add_front(t_list **llist, t_list *new);

void	add_back(t_list **llist, t_list *new);

void	free_linkedlist(t_list *llist);

void	free_linkedlist(t_list *llist)
{
	t_list	*temp_llist;
	t_list	*temp_ptr;

	temp_llist = llist;
	while (temp_llist)
	{
		temp_ptr = temp_llist;
		temp_llist = temp_llist->next;
		free(temp_ptr->num);
		free(temp_ptr);
	}
}

t_list	*lst_new(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	node->num = content;
	node->index = -1;
	node->next = NULL;
	return (node);
}

int	ft_lstsize(t_list *llist)
{
	t_list	*templst;
	int		size;

	if (!llist)
		return (0);
	size = 0;
	templst = llist;
	while (templst->next != NULL)
	{
		size++;
		templst = templst->next;
	}
	return (size + 1);
}

void	add_front(t_list **llist, t_list *new)
{
	if (!llist || !new)
		return ;
	new->next = *llist;
	*llist = new;
}

void	add_back(t_list **llist, t_list *new)
{
	t_list	*templst;

	if (!llist || !new)
		return ;
	templst = *llist;
	if (*llist == NULL)
	{
		*llist = new;
		return ;
	}
	while (templst->next)
		templst = templst->next;
	templst->next = new;
}

