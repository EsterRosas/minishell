/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:13:25 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/27 20:37:22 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	parent_process(int id, int status)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(id, &status, 0);
	ft_signal(1);
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
			write(1, "Quit: 3", 10);
		else if (g_exst == 130)
			write(1, "\n", 1);
		disable_ctrl_chars();
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
	if (check_cmd(prompt->cmd) == -1)
		return (g_exst);
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
