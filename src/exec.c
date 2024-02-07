/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:00:37 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/07 18:32:35 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_exbuiltin(t_prompt *prompt, t_cmd *cmd)
{
	if (ft_strcmp(cmd->args[0], "exit") == 0)
		ft_exit(prompt);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		ft_pwd(prompt->envp);
	else if (ft_strcmp(cmd->args[0], "echo") == 0)
		ft_echo(cmd);
	free_cmdlist(prompt->cmd);
	free_envlist(prompt->envp);
	free(prompt);
}

void	ft_execcmd(t_prompt *prompt, t_cmd *cmd, int fdin)
{
	// if (is_builtin(cmd->args[0]))
	// 	ft_exbuiltin(prompt, cmd);
	int		tmpout;	
	int		fdout;
	int		ret;

	tmpout = dup(1);
	dup2(fdin, 0);
	close(fdin);
	if (!cmd->next)
	{
		if (prompt->outfile_path)
			fdout = open(prompt->outfile_path, O_RDWR);
		else
			fdout = dup(tmpout);
	}
	else if (cmd)
	{

	}
}

void	ft_exec(t_prompt *prompt)
{
	t_cmd	*aux;
	int		tmpin;
	int		fdin;

	tmpin = dup(0);
	// Setup inital input TO-DO
	if (prompt->infile_path) 
		fdin = open(prompt->infile_path, O_RDONLY);
	else
		fdin = dup(tmpin);
	aux = prompt->cmd;
	while (aux)
	{
		ft_execcmd(prompt, aux, fdin);
		aux = aux->next;
	}
// GLOBAL FREE
}
