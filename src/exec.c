/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:00:37 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/14 17:59:40 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	execute_command(t_prompt *prompt, t_cmd *cmd)
{

}

void	ft_exbuiltin(t_prompt *prompt, t_cmd *cmd)
{
	if (ft_strcmp(cmd->args[0], "exit") == 0)
		ft_exit();
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		ft_pwd(prompt->envp);
	else if (ft_strcmp(cmd->args[0], "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		ft_env(prompt->envp);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		ft_cd(cmd);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		ft_unset(cmd/*, prompt->envp*/);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		ft_export(cmd->args, prompt->envp);
}

void	ft_execcmd(t_prompt *prompt, t_cmd *cmd)
{
	if (is_builtin(cmd->args[0]))
		ft_exbuiltin(prompt, cmd);
	else
		execute_command(prompt, cmd)
}

void	ft_exec(t_prompt *prompt)
{
	t_cmd	*aux;
	pid_t	pid;

	aux = prompt->cmd;
	while (aux)
	{
		ft_execcmd(prompt, aux);
		aux = aux->next;
	}
}

void	redir_and_exec(t_prompt *prompt)
{
	t_pipe	p;

	p.num_cmds = cmdlst_size();// TO-DO
	if (p.num_cmds == 0)
		g_exst = 0;
	else if (p.num_cmds == 1 && is_builtin(prompt->cmd->args[0]))
		g_exst = ft_exbuiltin(prompt, prompt->cmd);
	else
		g_exst = ft_exec(prompt);
}