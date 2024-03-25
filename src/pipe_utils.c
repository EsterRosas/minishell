/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:01:59 by damendez          #+#    #+#             */
/*   Updated: 2024/03/24 14:37:10 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	make_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
		handle_error("pipe", strerror(errno));
}

void	handle_read_end(int *pipe_fd)
{
	close(pipe_fd[W_END]);
	dup2(pipe_fd[R_END], STDIN_FILENO);
	close(pipe_fd[R_END]);
}

void	handle_write_end(int *pipe_fd)
{
	close(pipe_fd[R_END]);
	dup2(pipe_fd[W_END], STDOUT_FILENO);
	close(pipe_fd[W_END]);
}

void	update_pipes(t_pipe *p)
{
	if (p->i > 0)
	{
		close(p->prev_fds[R_END]);
		close(p->prev_fds[W_END]);
	}
	if (p->i < (p->num_cmds - 1))
	{
		p->prev_fds[R_END] = p->next_fds[R_END];
		p->prev_fds[W_END] = p->next_fds[W_END];
	}
}

void	handle_stdio(t_pipe *p, char *str)
{
	if (ft_strncmp("SAVE", str, 4) == 0)
	{
		p->tmpin = dup(0);
		p->tmpout = dup(1);
	}
	else if (ft_strncmp("RESTORE", str, 7) == 0)
	{
		dup2(p->tmpin, 0);
		dup2(p->tmpout, 1);
	}
}
