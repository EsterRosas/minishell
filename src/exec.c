/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:00:37 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/09 20:08:45 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
}

void	ft_execcmd(t_prompt *prompt, t_cmd *cmd)
{
	if (is_builtin(cmd->args[0]))
		ft_exbuiltin(prompt, cmd);
//else
}

void	ft_exec(t_prompt *prompt)
{
	t_cmd	*aux;

	aux = prompt->cmd;
	while (aux)
	{
		ft_execcmd(prompt, aux);
		aux = aux->next;
	}
}
