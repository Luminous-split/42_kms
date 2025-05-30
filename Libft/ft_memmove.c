/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:43:54 by ksan              #+#    #+#             */
/*   Updated: 2025/05/15 10:43:54 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n);

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*temp_dest;
	const unsigned char	*temp_src;

	temp_dest = (unsigned char *)dest;
	temp_src = (const unsigned char *)src;
	if (temp_dest < temp_src)
	{
		while (n--)
			*temp_dest++ = *temp_src++;
	}
	else
	{
		temp_dest += n;
		temp_src += n;
		while (n--)
			*(--temp_dest) = *(--temp_src);
	}
	return (dest);
}
