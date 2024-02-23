/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:00:37 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/21 20:51:23 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int	g_exst;

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
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		g_exst = ft_env(prompt->envp);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		g_exst = ft_cd(cmd);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		g_exst = ft_unset(cmd/*, prompt->envp*/);
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

static int	handle_cmd(t_prompt *prompt, t_cmd *cmd, t_pipe *p)
{
	/*
	 * TO-DO: link read/write ends of pipes to current command
	 * and return to exit_st
	*/
	if (p->i > 0)
	if (cmdlistsize(prompt->cmd) == 0)
		exit(EXIT_SUCCESS);
	ft_execcmd(prompt, cmd);
	return (EXIT_FAILURE);
}

static int	handle_cmds(t_pipe *p, t_prompt *prompt)
{
	t_cmd	*aux;
	pid_t	pid;
	pid_t	last_child;
	
	aux = prompt->cmd;
	p->i = -1
	while (aux)
	{
		p->i++;
		if (p->i < (p->num_cmds - 1)) // works?
			make_pipe();
		pid = make_fork();
		if (pid == 0)
			return (handle_cmd(prompt, aux)); // TO-FINISH
		//update_parent_pipe(); // TO-DO
		last_child = pid;
		aux = aux->next;
	}
	g_exst = wait_children(last_child, cmdlistsize(prompt->cmd));
	return (g_exst);
}

void	ft_exec(t_prompt *prompt)
{
	t_pipe	p;

	p.num_cmds = cmdlistsize(prompt->cmd);
	if (p.num_cmds == 0)
		g_exst = 0;
	else if (p.num_cmds == 1 && is_builtin(prompt->cmd->args[0]))
		//g_exst = ft_exbuiltin(prompt, prompt->cmd);
		ft_exbuiltin(prompt, prompt->cmd);
	else
		g_exst = handle_cmds(prompt);
}