/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printdigit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:54:19 by ksan              #+#    #+#             */
/*   Updated: 2025/05/27 14:54:19 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_printdigit(int n);

static void	printcount(int n, int *count);

int	ft_printdigit(int n)
{
	int	count;

	count = 0;
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		count += ft_printchar('-');
		n = -n;
	}
	printcount(n, &count);
	return (count);
}

static void	printcount(int n, int *count)
{
	if (n > 9)
		printcount(n / 10, count);
	*count += ft_printchar(n % 10 + '0');
}
