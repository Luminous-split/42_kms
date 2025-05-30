/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 13:29:10 by ksan              #+#    #+#             */
/*   Updated: 2025/05/17 13:29:10 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isset(char c, char const *set);

char		*ft_strtrim(char const *s1, char const *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	s1_len;
	size_t	head;
	size_t	tail;
	char	*trimmed_str;
	size_t	trimmed_slen;

	if (!s1 || !set)
		return (NULL);
	s1_len = ft_strlen(s1);
	head = 0;
	while (s1[head] != '\0' && ft_isset(s1[head], set))
		head++;
	tail = s1_len - 1;
	while (tail >= head && ft_isset(s1[tail], set))
		tail--;
	trimmed_slen = tail - head + 1;
	trimmed_str = (char *)malloc(sizeof(char) * (trimmed_slen + 1));
	if (!trimmed_str)
		return (NULL);
	ft_memcpy(trimmed_str, s1 + head, trimmed_slen);
	trimmed_str[trimmed_slen] = '\0';
	return (trimmed_str);
}

static int	ft_isset(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}
