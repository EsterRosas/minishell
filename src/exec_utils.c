/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:45:15 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/16 22:10:13 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exec_cmd(t_prompt *prompt, t_cmd *cmd)
{
	check_cmd(cmd);
	execve(cmd->full_path, cmd->args, env_lst2arr(prompt->envp));
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	exit(EXIT_FAILURE);
}

pid_t	make_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		handle_error("fork", strerror(errno));
	return (pid);
}

int	cmdlistsize(t_cmd *cmd)
{
	t_cmd	*aux;
	int		i;

	aux = cmd;
	i = 0;
	while (aux)
	{
		i++;
		aux = aux->next;
	}
	return (i);
}

int	wait_children(pid_t last_child, int n)
{
	pid_t	pid;
	int		i;
	int		status;
	int		last_status;

	i = -1;
	while (++i < n)
	{
		pid = wait(&status);
		if (pid == last_child)
			last_status = status;
	}
	if (WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	else if (WIFSIGNALED(last_status))
	{
		if (WTERMSIG(last_status) == SIGQUIT)
			ft_putstr_fd("Quit: 3", STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		return (WTERMSIG(last_status) + 128);
	}
	return (EXIT_FAILURE);
}
