/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 10:39:08 by ksan              #+#    #+#             */
/*   Updated: 2025/06/02 17:26:52 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line_bonus.h"
#include "pipex_bonus.h"

char	*ft_readline(char *read_line, int fd);

char	*ft_getline(char *line);

char	*get_next_line(int fd, char *limiter);

char	*ft_readline(char *line, int fd)
{
	char	*chunk_read;
	int		bytes_read;

	chunk_read = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!chunk_read)
		return (NULL);
	bytes_read = 1;
	while (!ft_gnl_strchr(line, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, chunk_read, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(chunk_read);
			return (NULL);
		}
		chunk_read[bytes_read] = '\0';
		line = ft_gnl_strjoin(line, chunk_read);
	}
	free(chunk_read);
	return (line);
}

char	*ft_getline(char *line)
{
	char	*result_line;
	int		i;

	i = 0;
	if (!line[i])
		return (NULL);
	while (line[i] && line[i] != '\n')
		i++;
	result_line = (char *)malloc(sizeof(char) * (i + 1));
	if (!result_line)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		result_line[i] = line[i];
		i++;
	}
	result_line[i] = '\0';
	return (result_line);
}

char	*get_next_line(int fd, char *limiter)
{
	static char	*line;
	char		*output_line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	line = ft_readline(line, fd);
	if (!line)
		return (NULL);
	output_line = ft_getline(line);
	if (check_heredoc(output_line, limiter) == 2)
		free(line);
	else
		line = ft_prep_nex_line(line);
	return (output_line);
}

/*
#include <fcntl.h>
#include <stdio.h>
//test
int	main(int argc, char **argv)
{
	if (argc >= 2)
		printf("Good More than 2 [argcs]\n");

	int	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		printf("fd less than 0");
	char *str;
	while ((str = get_next_line(fd)) != NULL)
	{
		printf("%s", str);
		free(str);
	}
	close(fd);
	return (0);
}

*/
