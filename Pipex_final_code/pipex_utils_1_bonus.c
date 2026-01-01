/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:32:11 by ksan              #+#    #+#             */
/*   Updated: 2025/06/25 18:14:22 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	**extract_path(char **envp);

static char	*prefix(char *cmd, const char *prefix_dir);

static void	free_path(char **path);

static void	parse_path_helper(t_list_args *cmds, char **path, int count);

void		parse_path(t_list_args *cmds, char **envp, int count);

static char	**extract_path(char **envp)
{
	char	**path;

	while (*envp)
	{
		if (!ft_strncmp(*envp, "PATH=", 5))
		{
			path = ft_split(*envp + 5, ':');
			return (path);
		}
		envp++;
	}
	return (NULL);
}

static char	*prefix(char *cmd, const char *prefix_dir)
{
	char	*out;
	size_t	prefix_len;
	size_t	cmd_len;

	prefix_len = ft_strlen(prefix_dir);
	cmd_len = ft_strlen(cmd);
	out = malloc(sizeof(char) * (prefix_len + cmd_len + 2));
	if (!out)
		return (NULL);
	ft_memcpy(out, prefix_dir, prefix_len);
	out[prefix_len] = '/';
	ft_memcpy(out + prefix_len + 1, cmd, cmd_len);
	out[prefix_len + cmd_len + 1] = '\0';
	return (out);
}

static void	free_path(char **path)
{
	int	i;

	i = -1;
	while (path[++i])
	{
		free(path[i]);
	}
	free(path);
}

static void	parse_path_helper(t_list_args *cmds, char **path, int count)
{
	int		i;
	int		j;
	char	*full_path;

	i = -1;
	while (++i < count)
	{
		j = -1;
		while (path[++j] && !(ft_strchr(cmds[i].args[0], '/'))
			&& ft_strlen(cmds[i].args[0]))
		{
			full_path = prefix(cmds[i].args[0], path[j]);
			if (access(full_path, X_OK) < 0)
			{
				free(full_path);
				continue ;
			}
			else
			{
				free(cmds[i].args[0]);
				cmds[i].args[0] = full_path;
				break ;
			}
		}
	}
}

void	parse_path(t_list_args *cmds, char **envp, int count)
{
	char	**path;

	path = extract_path(envp);
	if (!path)
		return ;
	parse_path_helper(cmds, path, count);
	free_path(path);
}
