/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:00:37 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/23 19:39:24 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_execcmd(t_prompt *prompt, t_cmd *cmd)
{
	if (is_builtin(cmd->args[0]))
		ft_exbuiltin(prompt, cmd);
	else
		exec_cmd(prompt, cmd);
	exit(EXIT_FAILURE);
}

static int	handle_cmd(t_prompt *prompt, t_cmd *cmd, t_pipe *p)
{
	/*
	 * TO-DO: manejar redirreciones desde handle_cmd 
	 * teniendo en cuenta el cmd 'i' actual ?
	*/
	if ((p->i) > 0) // NOT WORKING
	{
		handle_read_end(p->prev_fds);
		printf("linking read end from previous pipe as cmd input\n");
	}
	if ((p->i) < (p->num_cmds - 1)) // NOT WORKING
	{
		handle_write_end(p->next_fds);
		printf("linking write end from next pipe as cmd output\n");
	}
	if (cmdlistsize(prompt->cmd) == 0)
		exit(EXIT_SUCCESS);
	printf("gets to ft_execcmd in HANDLE_CMDS\n");
	ft_execcmd(prompt, cmd);
	return (EXIT_FAILURE);
}

static int	handle_cmds(t_prompt *prompt, t_pipe *p)
{
	t_cmd	*aux;
	pid_t	pid;
	pid_t	last_child;
	
	aux = prompt->cmd;
	p->i = -1;
	while (aux)
	{
		p->i++;
		if (p->i < (p->num_cmds - 1))
			make_pipe(p->next_fds);
		pid = make_fork();
		if (pid == 0)
			return (handle_cmd(prompt, aux, p)); // TO-FINISH
		update_pipes(p); // TO-DO
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
	else if (cmdlistsize(prompt->cmd) == 1 && is_builtin(prompt->cmd->args[0]))
		g_exst = ft_exbuiltin(prompt, prompt->cmd);
	else
		g_exst = handle_cmds(prompt, &p);
}
