/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 10:58:24 by ksan              #+#    #+#             */
/*   Updated: 2025/06/25 20:37:36 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	init_values(int *status, int *pid, int *i)
{
	*i = -1;
	*pid = 0;
	status[0] = 0;
	status[1] = 0;
}

static int	prepare_files(int argc, char **argv, int *inp_fd, int *out_fd)
{
	if (check_heredoc(argv[1], argv[2]) == 1)
	{
		*inp_fd = heredoc(argv[2]);
		*out_fd = open(argv[argc - 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
		return (1);
	}
	*inp_fd = open(argv[1], O_RDONLY);
	if (*inp_fd < 0)
	{
		perror(argv[1]);
		*out_fd = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (*out_fd < 0)
			perror(argv[argc - 1]);
		close(*out_fd);
		return (0);
	}
	*out_fd = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (*out_fd < 0)
	{
		close(*inp_fd);
		perror(argv[argc - 1]);
		return (0);
	}
	return (1);
}

static void	exec_and_free(int *fds, t_list_args *cmds, int ccount, int *es)
{
		*es = exec_cmds(fds, cmds, ccount,
				(int (*)(int*, int*, int*))init_values);
		free_all(cmds, ccount);
}

int	main(int argc, char **argv, char **envp)
{
	int			cmd_count;
	int			inp_fd;
	t_list_args	*cmds;
	int			out_fd;
	int			exit_status;

	cmd_count = 0;
	exit_status = 0;
	if (argc > 4)
	{
		if (!prepare_files(argc, argv, &inp_fd, &out_fd))
			return (1);
		if (out_fd != 1 && access(argv[argc -1], W_OK) != 0)
		{
			perror(argv[argc -1]);
			return (1);
		}
		cmds = cmd_parse(argc, argv, &cmd_count);
		parse_path(cmds, envp, cmd_count);
		exec_and_free((int []){inp_fd, out_fd}, cmds, cmd_count, &exit_status);
		close(out_fd);
	}
	else
		ft_putstr_fd("./pipex ifile/(here_doc limiter) c1 c2 ...cn ofile\n", 1);
	return (exit_status);
}
