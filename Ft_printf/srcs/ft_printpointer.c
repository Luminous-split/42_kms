/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printpointer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:53:07 by ksan              #+#    #+#             */
/*   Updated: 2025/05/27 13:53:07 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int				count(unsigned long long n);

static void				print_address(unsigned long long n);

int						ft_printpointer(void *address);

int	ft_printpointer(void *address)
{
	int					final_count;
	unsigned long long	n;

	n = (unsigned long long)address;
	if (n == 0)
		return (ft_printstr("(nil)"));
	final_count = count(n) + 2;
	write(1, "0x", 2);
	print_address(n);
	return (final_count);
}

static int	count(unsigned long long n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		count++;
		n /= 16;
	}
	return (count);
}

static void	print_address(unsigned long long n)
{
	static char	*hexchars;

	hexchars = "0123456789abcdef";
	if (n >= 16)
		print_address(n / 16);
	write(1, &hexchars[n % 16], 1);
}
