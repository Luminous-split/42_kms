/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:16:25 by ksan              #+#    #+#             */
/*   Updated: 2025/05/15 18:16:25 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c);

char	*ft_strrchr(const char *s, int c)
{
	const unsigned char	*temp_s;
	char				*lst_ocr;

	lst_ocr = NULL;
	temp_s = (const unsigned char *)s;
	while (*temp_s != '\0')
	{
		if (*temp_s == (unsigned char)c)
			lst_ocr = (char *)temp_s;
		temp_s++;
	}
	if (*temp_s == (unsigned char)c)
		return ((char *)temp_s);
	return (lst_ocr);
}
