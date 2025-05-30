/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 11:54:11 by ksan              #+#    #+#             */
/*   Updated: 2025/05/18 11:54:11 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd);

void	ft_putstr_fd(char *s, int fd)
{
	size_t	s_len;
	size_t	i;

	if (!s)
		return ;
	s_len = ft_strlen(s);
	i = 0;
	while (i < s_len)
	{
		write(fd, &s[i], 1);
		i++;
	}
}
