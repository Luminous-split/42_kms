/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 11:02:52 by ksan              #+#    #+#             */
/*   Updated: 2025/05/18 11:02:52 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	size_t			s_size;
	char			*final_str;

	if (!s)
		return (NULL);
	i = 0;
	s_size = ft_strlen(s);
	final_str = (char *)malloc(sizeof(char) * (s_size + 1));
	if (!final_str)
		return (NULL);
	while (i < s_size)
	{
		final_str[i] = f(i, s[i]);
		i++;
	}
	final_str[s_size] = '\0';
	return (final_str);
}
