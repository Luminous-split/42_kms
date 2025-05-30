/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:29:05 by ksan              #+#    #+#             */
/*   Updated: 2025/05/15 18:29:05 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n);

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	s1i;
	unsigned char	s2i;
	size_t			i;

	i = 0;
	while (i < n)
	{
		s1i = (unsigned char)s1[i];
		s2i = (unsigned char)s2[i];
		if (s1i != s2i)
			return (s1i - s2i);
		if (s1i == '\0')
			return (0);
		i++;
	}
	return (0);
}
