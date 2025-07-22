/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:52:58 by ksan              #+#    #+#             */
/*   Updated: 2025/05/15 18:52:58 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size);

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	l_len;

	i = 0;
	if (!big)
		return (NULL);
	if (!little)
		return (NULL);
	if (little[0] == '\0')
		return ((char *)big);
	l_len = ft_strlen(little);
	while (i + l_len <= len)
	{
		if (big[i] == '\0')
			break ;
		if (ft_strncmp(big + i, little, l_len) == 0)
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}
