/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:20:19 by ksan              #+#    #+#             */
/*   Updated: 2025/05/15 17:20:19 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size);

size_t	ft_strnlen(const char *s, size_t maxlen)
{
	size_t	i;

	i = 0;
	while (i < maxlen && s[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	cp_size;

	if (!dst || !src)
		return (0);
	dst_len = ft_strnlen(dst, size);
	src_len = ft_strlen(src);
	cp_size = 0;
	if (size == 0)
		return (src_len);
	if (dst_len != size)
	{
		cp_size = size - dst_len - 1;
		if (cp_size > src_len)
			cp_size = src_len;
		ft_memcpy(dst + dst_len, src, cp_size);
		dst[dst_len + cp_size] = '\0';
	}
	return (dst_len + src_len);
}
