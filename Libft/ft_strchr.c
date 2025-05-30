/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:56:15 by ksan              #+#    #+#             */
/*   Updated: 2025/05/15 17:56:15 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c);

char	*ft_strchr(const char *s, int c)
{
	const unsigned char	*temp_s;

	temp_s = (const unsigned char *)s;
	while (*temp_s != '\0')
	{
		if (*temp_s == (unsigned char)c)
			return ((char *)temp_s);
		temp_s++;
	}
	if (*temp_s == (unsigned char)c)
		return ((char *)temp_s);
	return (NULL);
}
