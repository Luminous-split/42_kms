/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:54:41 by ksan              #+#    #+#             */
/*   Updated: 2025/05/17 14:54:41 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c);

static char	**ft_insert_words(char **splitted, char const *s, char c);

static char	**ft_freesplit(char **arr, size_t i);

static char	*ft_word_split(char const *s, size_t length);

char		**ft_split(char const *s, char c);

char	**ft_split(char const *s, char c)
{
	char		**splitted;
	int			wc;

	if (!s)
		return (NULL);
	wc = ft_count_words(s, c);
	splitted = (char **)malloc(sizeof(char *) * (wc + 1));
	if (!splitted)
		return (NULL);
	splitted[wc] = (NULL);
	splitted = ft_insert_words(splitted, s, c);
	return (splitted);
}

static char	**ft_insert_words(char **splitted, char const *s, char c)
{
	const char	*word;
	size_t		indiv_slen;
	int			i;

	i = 0;
	while (*s != '\0')
	{
		if (*s != c)
		{
			word = s;
			indiv_slen = 0;
			while (*s != '\0' && *s != c)
			{
				s++;
				indiv_slen++;
			}
			splitted[i] = ft_word_split(word, indiv_slen);
			if (!splitted[i])
				return (ft_freesplit(splitted, i));
			i++;
		}
		else
			s++;
	}
	return (splitted);
}

static int	ft_count_words(char const *s, char c)
{
	int	count;
	int	i;
	int	is_in_word;

	i = 0;
	count = 0;
	is_in_word = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && is_in_word == 0)
		{
			is_in_word = 1;
			count++;
		}
		else if (s[i] == c)
			is_in_word = 0;
		i++;
	}
	return (count);
}

static char	*ft_word_split(char const *s, size_t length)
{
	char	*word;

	word = (char *)malloc((sizeof(char) * length) + 1);
	if (!word)
		return (NULL);
	ft_memcpy(word, s, length);
	word[length] = '\0';
	return (word);
}

static char	**ft_freesplit(char **arr, size_t i)
{
	while (i--)
		free(arr[i]);
	free(arr);
	return (NULL);
}
