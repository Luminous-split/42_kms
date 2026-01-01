/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec_cmd_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 13:08:54 by ksan              #+#    #+#             */
/*   Updated: 2026/01/01 13:20:26 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	get_exitcode(int err_no)
{
	if (err_no == ENOENT)
		return (127);
	else if (err_no == EACCES || err_no == EISDIR || err_no == ENOEXEC
		|| err_no == ETXTBSY || err_no == ELOOP || err_no == ENAMETOOLONG
		|| err_no == ENOTDIR)
		return (126);
	else
		return (1);
}

static int	child_func(int *pipefd, int *out_fd, int *idx, t_list_args *cmds)
{
	int	i;
	int	count;

	i = idx[0];
	count = idx[1];
	close(pipefd[0]);
	if (i < count - 1)
		dup2(pipefd[1], 1);
	else if (*out_fd)
	{
		dup2(*out_fd, 1);
		close(*out_fd);
	}
	close(pipefd[1]);
	if (execve(cmds[i].args[0], cmds[i].args, NULL) == -1)
	{
		perror(cmds[i].args[0]);
		return (get_exitcode(errno));
	}
	return (0);
}

static void	parent(int *pipefd, int *entry_fd, int i, int count)
{
	close(pipefd[1]);
	if (*entry_fd > 0)
		close(*entry_fd);
	if (i < count - 1)
		*entry_fd = pipefd[0];
	else
		close(pipefd[0]);
}

static void	cleanup_child(t_list_args *cmds, int status, int *out_fd, int *vals)
{
	if (status != 0)
	{
		free_all(cmds, vals[1]);
		close(0);
		close(1);
		if (vals[0] < vals[1] - 1)
			close(*out_fd);
		exit(status);
	}
}

int	exec_cmds(int *in_out_fds, t_list_args *cmds, int count,
	int (*func_ptr)(int*, int*, int*))
{
	int	i;
	int	pipefd[2];
	int	status[2];
	int	pid;

	func_ptr(status, &pid, &i);
	while (++i < count)
	{
		pipe(pipefd);
		pid = fork();
		if (pid == 0)
		{
			dup2(in_out_fds[0], 0);
			close(in_out_fds[0]);
			status[1] = child_func(pipefd, &in_out_fds[1],
					(int []){i, count}, cmds);
			cleanup_child(cmds, status[1], &in_out_fds[1], (int []){i, count});
		}
		else
			parent(pipefd, &in_out_fds[0], i, count);
		while (waitpid(pid, &status[0], 0) > 0)
			continue ;
	}
	return (WEXITSTATUS(status[0]));
}
