/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 18:32:51 by ksan              #+#    #+#             */
/*   Updated: 2025/06/25 13:56:00 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_convert(char *finalstr, int str_len, long temp_n1);

char		*ft_itoa(int n);

char	*ft_itoa(int n)
{
	int		temp_n1;
	char	*finalstr;
	int		str_len;

	temp_n1 = n;
	if (n <= 0)
		str_len = 1;
	else
		str_len = 0;
	while (temp_n1 != 0)
	{
		str_len++;
		temp_n1 /= 10;
	}
	finalstr = (char *)malloc(sizeof(char) * (str_len + 1));
	if (!finalstr)
		return (NULL);
	finalstr[str_len] = '\0';
	temp_n1 = (long)n;
	finalstr = ft_convert(finalstr, str_len, temp_n1);
	return (finalstr);
}

static char	*ft_convert(char *finalstr, int str_len, long temp_n1)
{
	int	negative;

	negative = 0;
	if (temp_n1 < 0)
	{
		negative = 1;
		temp_n1 = -temp_n1;
	}
	while (str_len > 0)
	{
		finalstr[--str_len] = (temp_n1 % 10) + '0';
		temp_n1 /= 10;
	}
	if (negative)
		finalstr[0] = '-';
	return (finalstr);
}
