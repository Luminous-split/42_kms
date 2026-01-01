/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:24:50 by ksan              #+#    #+#             */
/*   Updated: 2025/06/25 20:37:05 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char		*ft_gnl_strchr(char *s, int c);

static char	*ft_joinstrings(char *s1, char *s2, char *result, int s1_len);

char		*ft_gnl_strjoin(char *s1, char *s2);

char		*ft_prep_nex_line(char *line);

int			ft_gnl_strlen(char *s);

int	ft_gnl_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_gnl_strchr(char *s, int c)
{
	int	i;

	if (!s)
		return (0);
	if (c == '\0')
		return (&s[ft_gnl_strlen(s)]);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (&s[i]);
		i++;
	}
	return (0);
}

static	char	*ft_joinstrings(char *s1, char *s2, char *result, int s1_len)
{
	int	i;

	i = -1;
	while (s1[++i])
		result[i] = s1[i];
	i = -1;
	while (s2[++i])
		result[s1_len + i] = s2[i];
	result[s1_len + ft_gnl_strlen(s2)] = '\0';
	return (result);
}

char	*ft_gnl_strjoin(char*s1, char *s2)
{
	char	*result;
	int		s1_len;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	if (!s2)
	{
		free(s1);
		return (NULL);
	}
	s1_len = ft_gnl_strlen(s1);
	result = (char *)malloc(sizeof(char) * (s1_len + ft_gnl_strlen(s2) + 1));
	if (!result)
		return (NULL);
	result = ft_joinstrings(s1, s2, result, s1_len);
	free(s1);
	return (result);
}

char	*ft_prep_nex_line(char *line)
{
	char	*new_str;
	int		i;
	int		k;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (!line[i])
	{
		free(line);
		return (NULL);
	}
	new_str = (char *)malloc(sizeof(char) * (ft_gnl_strlen(line) - i + 1));
	if (!new_str)
		return (NULL);
	i = i + 1;
	k = 0;
	while (line[i] != '\0')
		new_str[k++] = line[i++];
	new_str[k] = '\0';
	free(line);
	return (new_str);
}
