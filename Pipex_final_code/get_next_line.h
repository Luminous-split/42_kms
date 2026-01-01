/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 13:10:00 by ksan              #+#    #+#             */
/*   Updated: 2025/06/25 18:12:56 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>

char	*ft_gnl_strchr(char *s, int c);

char	*ft_gnl_strjoin(char *s1, char *s2);

char	*ft_getline(char *line);

char	*ft_prep_nex_line(char *line);

char	*get_next_line(int fd, char *limiter);

int		ft_gnl_strlen(char *s);

#endif
