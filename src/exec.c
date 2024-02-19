/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:00:37 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/17 13:51:16 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

pid_t	make_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit (EXIT_FAILURE);
	return (pid);
}

void	exec_cmd(t_prompt *prompt, t_cmd *cmd)
{
	execve(cmd->full_path, cmd->args, env_lst2arr(prompt->envp));
	// error message incase of error TO-DO
	exit (EXIT_FAILURE);
}

void	ft_exbuiltin(t_prompt *prompt, t_cmd *cmd)
{
	if (ft_strcmp(cmd->args[0], "exit") == 0)
		ft_exit();
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		g_exst = ft_pwd(prompt->envp);
	else if (ft_strcmp(cmd->args[0], "echo") == 0)
		g_exst = ft_echo(cmd);
	else if (is_env(cmd->args[0]))
		g_exst = ft_env(prompt->envp);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		g_exst = ft_cd(cmd);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		g_exst = ft_unset(cmd, prompt->envp);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		g_exst = ft_export(cmd->args, prompt->envp);
}

void	ft_execcmd(t_prompt *prompt, t_cmd *cmd)
{
	if (is_builtin(cmd->args[0]))
		ft_exbuiltin(prompt, cmd);
	exec_cmd(prompt, cmd);
	exit(EXIT_FAILURE);
}

static int	handle_cmd(t_prompt *prompt, t_cmd *cmd)
{
	/*
	 * TO-DO: link read/write ends of pipes to current command
	 * and return to exit_st
	*/
	if (cmdlistsize(prompt->cmd) == 0)
		exit(EXIT_SUCCESS);
	ft_execcmd(prompt, cmd);
	return (EXIT_FAILURE);
}

static int	handle_cmds(t_prompt *prompt)
{
	t_cmd	*aux;
	//int		exit_st;
	pid_t	pid;
//	pid_t	last_child;
	
	aux = prompt->cmd;
	while (aux)
	{
		if (aux->next)
			//make_pipe(); // TO-DO
		pid = make_fork();
		if (pid == 0)
			return (handle_cmd(prompt, aux)); // TO-FINISH
		//update_parent_pipe(); // TO-DO
//		last_child = pid;
		aux = aux->next;
	}
	//exit_st = wait_children(last_child, cmdlistsize(prompt->cmd)); // TO-DO
	//return (exit_st);
	return (0);
}

void	ft_exec(t_prompt *prompt)
{
	if (cmdlistsize(prompt->cmd) == 0)
		g_exst = 0;
	else if (cmdlistsize(prompt->cmd) == 1 && is_builtin(prompt->cmd->args[0]))
		//g_exst = ft_exbuiltin(prompt, prompt->cmd);
		ft_exbuiltin(prompt, prompt->cmd);
	else
		g_exst = handle_cmds(prompt);
}
