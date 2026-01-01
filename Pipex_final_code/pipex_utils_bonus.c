/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:32:11 by ksan              #+#    #+#             */
/*   Updated: 2025/06/25 20:38:48 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

t_list_args	*cmd_parse(int argc, char *argv[], int *cmd_count);

void		*ft_realloc(void *ptr, size_t old_size, size_t new_size);

static void	trim_cmdargs(char **cmd);

int			check_heredoc(char *arg, char *limiter);

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	size_t	copysize;
	void	*new_ptr;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (!ptr)
		return (new_ptr);
	if (old_size < new_size)
		copysize = old_size;
	else
		copysize = new_size;
	ft_memcpy(new_ptr, ptr, copysize);
	free(ptr);
	return (new_ptr);
}

static void	validate_heredoc(char **argv, int *cmd_start)
{
	if (check_heredoc(argv[1], argv[2]) == 1)
		*cmd_start = 3;
	else
		*cmd_start = 2;
}

t_list_args	*cmd_parse(int argc, char **argv, int *cmd_count)
{
	int			cmd_start;
	t_list_args	*cmds;
	t_list_args	cmd;

	cmds = NULL;
	validate_heredoc(argv, &cmd_start);
	while (cmd_start < argc - 1)
	{
		cmd.args = ft_split(argv[cmd_start], ' ');
		if (cmd.args[0] == NULL)
		{
			free(cmd.args);
			cmd.args = malloc(sizeof(char *) * 2);
			cmd.args[0] = ft_strdup(argv[cmd_start]);
			cmd.args[1] = NULL;
		}
		trim_cmdargs(cmd.args);
		cmds = ft_realloc(cmds, (*cmd_count) * sizeof(t_list_args),
				((*cmd_count) + 1) * sizeof(t_list_args));
		cmds[(*cmd_count)++] = cmd;
		cmd_start++;
	}
	return (cmds);
}

static void	trim_cmdargs(char **cmd)
{
	int	j;

	j = 0;
	while (cmd[++j])
		cmd[j] = ft_strtrim(cmd[j]);
}

int	check_heredoc(char *arg, char *limiter)
{
	char	*temp;

	temp = limiter;
	if (ft_strncmp(arg, "here_doc", ft_strlen("here_doc")) == 0
		&& ft_strlen(arg) == ft_strlen("here_doc"))
		return (1);
	else if (ft_strncmp(arg, temp, ft_strlen(temp)) == 0
		&& ft_strlen(arg) == ft_strlen(temp))
		return (2);
	return (0);
}
