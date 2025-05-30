/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printchex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:38:15 by ksan              #+#    #+#             */
/*   Updated: 2025/05/27 16:38:15 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	printcount(unsigned int n, int *count);

int			ft_printchex(unsigned int n);

int	ft_printchex(unsigned int n)
{
	int	count;

	count = 0;
	printcount(n, &count);
	return (count);
}

static void	printcount(unsigned int n, int *count)
{
	static char	*hexchars;

	hexchars = "0123456789ABCDEF";
	if (n >= 16)
		printcount(n / 16, count);
	*count += ft_printchar(hexchars[n % 16]);
}
