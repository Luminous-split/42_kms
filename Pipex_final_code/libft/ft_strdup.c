/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:45:26 by ksan              #+#    #+#             */
/*   Updated: 2025/05/16 13:45:26 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s);

char	*ft_strdup(const char *s)
{
	size_t	s_len;
	char	*new_str;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s) + 1;
	new_str = malloc(s_len);
	if (new_str == NULL)
		return (NULL);
	new_str = ft_memcpy(new_str, s, s_len);
	return (new_str);
}
