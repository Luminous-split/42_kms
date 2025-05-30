/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:23:48 by ksan              #+#    #+#             */
/*   Updated: 2025/05/27 13:23:48 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printstr(char *str)
{
	int	s_len;

	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	s_len = ft_strlen(str);
	write(1, str, ft_strlen(str));
	return (s_len);
}
