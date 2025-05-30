/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:39:08 by ksan              #+#    #+#             */
/*   Updated: 2025/05/26 12:39:08 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_parser(const char c, va_list args);

int			ft_printf(const char *format, ...);

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		total_printed;

	total_printed = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			total_printed += ft_parser(*format, args);
		}
		else
			total_printed += ft_printchar(*format);
		format++;
	}
	va_end(args);
	return (total_printed);
}

static int	ft_parser(const char c, va_list args)
{
	int	total_printed;

	total_printed = 0;
	if (c == 'c')
		total_printed += ft_printchar(va_arg(args, int));
	else if (c == 's')
		total_printed += ft_printstr(va_arg(args, char *));
	else if (c == '%')
		total_printed += ft_printchar('%');
	else if (c == 'p')
		total_printed += ft_printpointer(va_arg(args, void *));
	else if (c == 'd' || c == 'i')
		total_printed += ft_printdigit(va_arg(args, int));
	else if (c == 'u')
		total_printed += ft_printunsigned(va_arg(args, unsigned int));
	else if (c == 'x')
		total_printed += ft_printhex(va_arg(args, unsigned int));
	else if (c == 'X')
		total_printed += ft_printchex(va_arg(args, unsigned int));
	return (total_printed);
}
