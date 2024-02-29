/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:45:15 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/29 20:26:00 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_cmd(t_cmd *cmd)
{
	if (cmd->full_path == NULL)
	{
		if (ft_strcmp(cmd->args[0], "$\?") == 0)
		{
			printf("minishell: %i: command not found\n", g_exst);
		}
		else
		{
		//	printf("minishell: %s: command not found\n", cmd->args[0]);
			handle_error(cmd->args[0], "command not found");
		}
		g_exst = 127;
		return (-1);
	}
	return (0);
}

void	exec_cmd(t_prompt *prompt, t_cmd *cmd)
{
	check_cmd(cmd);
	execve(cmd->full_path, cmd->args, env_lst2arr(prompt->envp));
	exit (EXIT_FAILURE);
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
