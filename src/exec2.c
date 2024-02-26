/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:13:25 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/26 20:15:27 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	exec_child(t_cmd *cmd, char **env)
{	
	ft_signal(0);
	restore_terminal_settings();
	//	FALTEN ELS DUPS PER QUAN EL CMD TINGUI UN INPUT O OUTPUT QUE NO SIGUIN ELS ESTANDARDS
	execve(cmd->full_path, cmd->args, env);
	printf("minishell: %s: %s\n", cmd->args[0], strerror(errno));
	exit (127);
}

int	onecmd_nobuilt(t_prompt *prompt)
{
	int	id;
	int	status;

	if (check_cmd(prompt->cmd) == -1)
		return (g_exst);
	id = make_fork();
	if (id == 0)
		exec_child(prompt->cmd, env_lst2arr(prompt->envp));
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(id, &status, 0);
		ft_signal(1);
	}
	if (WIFEXITED(status))
		g_exst = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
	//	child_signal();
		g_exst = WTERMSIG(status) + 128;
		if (g_exst == 131)
			write(1, "Quit: 3", 10);
		else if (g_exst == 130)
			write(1, "\n", 1);
		disable_ctrl_chars();
	}
	return (g_exst);
}
