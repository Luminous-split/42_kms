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

static int	ft_ismatch(char head, char tail);

static int	ft_isquote(char target, char c);

char		*ft_strtrim(char *s1);

char	*ft_strtrim(char *s1)
{
	size_t	s1_len;
	size_t	head;
	size_t	tail;
	char	*trimmed_str;
	size_t	trimmed_slen;

	if (!s1)
		return (NULL);
	s1_len = ft_strlen(s1);
	head = 0;
	tail = s1_len - 1;
	if (ft_ismatch(s1[head], s1[tail]))
	{
		head++;
		tail--;
	}
	trimmed_slen = tail - head + 1;
	trimmed_str = (char *)malloc(sizeof(char) * (trimmed_slen + 1));
	if (!trimmed_str)
		return (NULL);
	ft_memcpy(trimmed_str, s1 + head, trimmed_slen);
	trimmed_str[trimmed_slen] = '\0';
	free(s1);
	return (trimmed_str);
}

static int	ft_ismatch(char head, char tail)
{
	if (ft_isquote(head, 39) && ft_isquote(tail, 39))
		return (1);
	else if (ft_isquote(head, 34) && ft_isquote(tail, 34))
		return (1);
	return (0);
}

static int	ft_isquote(char target, char c)
{
	return (target == c);
}
