/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:38:49 by ksan              #+#    #+#             */
/*   Updated: 2025/05/15 11:38:49 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n);

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		i;
	const unsigned char	*temp_s;

	i = c;
	temp_s = s;
	while (n--)
	{
		if (*temp_s == i)
			return ((void *)temp_s);
		temp_s++;
	}
	return (NULL);
}
