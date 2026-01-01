/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:59:29 by ksan              #+#    #+#             */
/*   Updated: 2025/05/13 17:59:29 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

int	ft_atoi(const char *nptr);

int	ft_atoi(const char *nptr)
{
	long long	final;
	int			sign;

	final = 0;
	sign = 1;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		final = (final * 10) + (*nptr - '0');
		nptr++;
	}
	final = final * sign;
	if (final > INT_MAX)
		return (0);
	else if (final < INT_MIN)
		return (-1);
	return ((int)final);
}
