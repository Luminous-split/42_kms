/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:17:44 by ksan              #+#    #+#             */
/*   Updated: 2025/05/19 12:17:44 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst);

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*templst;

	if (!lst)
		return (NULL);
	templst = lst;
	while (templst->next != NULL)
		templst = templst->next;
	return (templst);
}
