/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:45:56 by ksan              #+#    #+#             */
/*   Updated: 2025/05/16 16:45:56 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_fail(char *ss);

static char	*ft_success(char *ss, char const *s, unsigned int st, size_t len);

char		*ft_substr(char const *s, unsigned int start, size_t len);

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*ss;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len < start)
	{
		ss = (char *)malloc(sizeof(char) * 1);
		ss = ft_fail(ss);
		return (ss);
	}
	if ((s_len - start) < len)
		len = s_len - start;
	ss = (char *)malloc(sizeof(char) * (len + 1));
	ss = ft_success(ss, s, start, len);
	return (ss);
}

static char	*ft_fail(char *ss)
{
	if (!ss)
		return (NULL);
	ss[0] = '\0';
	return (ss);
}

static char	*ft_success(char *ss, char const *s, unsigned int st, size_t len)
{
	if (!ss)
		return (NULL);
	ft_memcpy(ss, s + st, len);
	ss[len] = '\0';
	return (ss);
}
