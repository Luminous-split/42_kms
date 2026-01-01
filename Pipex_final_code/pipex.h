/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:58:41 by ksan              #+#    #+#             */
/*   Updated: 2025/06/25 18:14:40 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include "libft/libft.h"

typedef struct s_list_args
{
	char	**args;
}	t_list_args;

t_list_args	*cmd_parse(int argc, char *argv[], int cmd_start, int *cmd_count);

void		*ft_realloc(void *ptr, size_t old_size, size_t new_size);

void		parse_path(t_list_args *cmds, char **envp, int count);

void		free_all(t_list_args *cmds, int count);

int			exec_cmds(int *in_out_fds, t_list_args *cmds, int count,
				int (*func_ptr)(int*, int*, int*));

int			ft_heredoc(int argc, char *arg, int *outfile_fd);

#endif
