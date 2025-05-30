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
	void	*temp_str;
	char	*n_str;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s) + 1;
	temp_str = malloc(s_len);
	if (temp_str == NULL)
		return (NULL);
	n_str = ft_memcpy(temp_str, s, s_len);
	return (n_str);
}
