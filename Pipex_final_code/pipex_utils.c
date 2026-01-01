/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:32:11 by ksan              #+#    #+#             */
/*   Updated: 2025/06/25 18:14:31 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_list_args	*cmd_parse(int argc, char *argv[], int cmd_start, int *cmd_count);

void		*ft_realloc(void *ptr, size_t old_size, size_t new_size);

void		free_all(t_list_args *cmds, int count);

static void	trim_cmdargs(char **cmd);

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

t_list_args	*cmd_parse(int argc, char *argv[], int cmd_start, int *cmd_count)
{
	t_list_args	*cmds;
	t_list_args	cmd;
	int			next_size;

	cmds = NULL;
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
		next_size = ((*cmd_count) + 1) * sizeof(t_list_args);
		cmds = ft_realloc(cmds, (*cmd_count) * sizeof(t_list_args), next_size);
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
