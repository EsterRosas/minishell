/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:13:25 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/21 17:39:48 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	parent_process(int id, int status)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(id, &status, 0);
	disable_ctrl_chars();
	return (status);
}

void	child_signaled(int status)
{
	if (WIFEXITED(status))
		g_exst = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		g_exst = WTERMSIG(status) + 128;
		if (g_exst == 131)
			write(2, "Quit: 3", 10);
		else if (g_exst == 130)
			write(2, "\n", 1);
	}
}

static void	exec_child(t_cmd *cmd, char **env)
{
	ft_signal(0);
	restore_terminal_settings();
	dup2(cmd->infile, STDIN_FILENO);
	dup2(cmd->outfile, STDOUT_FILENO);
	execve(cmd->full_path, cmd->args, env);
	printf("minishell: %s: %s\n", cmd->args[0], strerror(errno));
	exit (127);
}

int	onecmd_nobuilt(t_prompt *prompt)
{
	int	id;
	int	status;
	int	saved_stdin;
	int	saved_stdout;

	status = 0;
	check_cmd(prompt->cmd);
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	id = make_fork();
	if (id == 0)
		exec_child(prompt->cmd, env_lst2arr(prompt->envp));
	else
		status = parent_process(id, status);
	child_signaled(status);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	return (g_exst);
}
