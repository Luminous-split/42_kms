/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:09:29 by ksan              #+#    #+#             */
/*   Updated: 2025/05/27 13:09:29 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <stddef.h>

int		ft_printf(const char *format, ...);
int		ft_printstr(char *str);
int		ft_printpointer(void *address);
int		ft_printdigit(int n);
int		ft_printchar(char c);
int		ft_printunsigned(unsigned int n);
int		ft_printhex(unsigned int n);
int		ft_printchex(unsigned int n);
size_t	ft_strlen(const char *s);
