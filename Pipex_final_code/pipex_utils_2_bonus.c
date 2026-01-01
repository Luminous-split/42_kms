/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:24:40 by ksan              #+#    #+#             */
/*   Updated: 2025/06/27 16:47:33 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "get_next_line_bonus.h"

static void	putlines(char *limiter, int fd);

void		free_all(t_list_args *cmds, int count);

int			heredoc(char *limiter);

void	free_all(t_list_args *cmds, int count)
{
	int	i;
	int	j;

	i = -1;
	while (++i < count)
	{
		j = 0;
		while (cmds[i].args[j])
		{
			free(cmds[i].args[j]);
			j++;
		}
		free(cmds[i].args);
	}
	free(cmds);
}

static void	putlines(char *limiter, int fd)
{
	char	*str;

	while (1)
	{
		str = get_next_line(0, limiter);
		if (check_heredoc(str, limiter) == 2 || str == NULL)
		{
			free(str);
			break ;
		}
		ft_putendl_fd(str, fd);
		free(str);
	}
}

int	heredoc(char *limiter)
{
	int	pipefd[2];

	if (pipe(pipefd) < 0)
	{
		perror("pipe failed");
		exit(1);
	}
	if (fork() == 0)
	{
		close(pipefd[0]);
		putlines(limiter, pipefd[1]);
		close(pipefd[1]);
		exit(0);
	}
	wait(NULL);
	close(pipefd[1]);
	return (pipefd[0]);
}
