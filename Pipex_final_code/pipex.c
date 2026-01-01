/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 10:58:24 by ksan              #+#    #+#             */
/*   Updated: 2025/06/25 18:14:00 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	init_values(int *status, int *pid, int *i)
{
	*i = -1;
	*pid = 0;
	status[0] = 0;
	status[1] = 0;
}

static int	prepare_files(int argc, char **argv, int *inp_fd, int *out_fd)
{
	*inp_fd = open(argv[1], O_RDONLY);
	if (*inp_fd < 0)
	{
		perror(argv[1]);
		*out_fd = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (*out_fd < 0)
			perror(argv[argc - 1]);
		close(*out_fd);
		return (1);
	}
	*out_fd = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (*out_fd < 0)
	{
		close(*inp_fd);
		perror(argv[argc - 1]);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int			cmd_count;
	int			inp_fd;
	int			out_fd;
	int			exit_status;
	t_list_args	*cmds;

	cmd_count = 0;
	exit_status = 0;
	if (argc > 3)
	{
		exit_status = prepare_files(argc, argv, &inp_fd, &out_fd);
		if (exit_status)
			return (1);
		cmds = cmd_parse(argc, argv, 2, &cmd_count);
		parse_path(cmds, envp, cmd_count);
		exit_status = exec_cmds((int []){inp_fd, out_fd}, cmds, cmd_count,
				(int (*)(int*, int*, int*))init_values);
		free_all(cmds, cmd_count);
		close(out_fd);
	}
	else
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile \n", 1);
	return (exit_status);
}
