/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printunsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:52:57 by ksan              #+#    #+#             */
/*   Updated: 2025/05/27 15:52:57 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_printunsigned(unsigned int n);

static void	printcount(unsigned int n, int *count);

int	ft_printunsigned(unsigned int n)
{
	int	count;

	count = 0;
	printcount(n, &count);
	return (count);
}

static void	printcount(unsigned int n, int *count)
{
	if (n > 9)
		printcount(n / 10, count);
	*count += ft_printchar(n % 10 + '0');
}
