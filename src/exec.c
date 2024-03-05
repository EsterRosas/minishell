/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:00:37 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/05 15:31:01 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_redirs(t_cmd *cmd, t_pipe *p)
{
	if (p->i == 0)
		dup2(cmd->infile, STDIN_FILENO);
	if (p->i == p->num_cmds - 1)
		dup2(cmd->outfile, STDOUT_FILENO);
}

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
	restore_terminal_settings();
	handle_redirs(cmd, p);
	if (p->i > 0)
		handle_read_end(p->prev_fds);
	if (p->i < (p->num_cmds - 1))
		handle_write_end(p->next_fds);
	if (cmdlistsize(prompt->cmd) == 0)
		exit(EXIT_SUCCESS);
	if (check_cmd(cmd) == -1)
		return (g_exst);
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
			return (handle_cmd(prompt, aux, p));
		update_pipes(p);
		last_child = pid;
		aux = aux->next;
	}
	g_exst = wait_children(last_child, cmdlistsize(prompt->cmd));
	disable_ctrl_chars();
	return (g_exst);
}

void	ft_exec(t_prompt *prompt)
{
	t_pipe	p;

	handle_stdio(&p, "SAVE");
	p.num_cmds = cmdlistsize(prompt->cmd);
	if (p.num_cmds == 0)
		g_exst = 0;
	else if (p.num_cmds == 1 && is_builtin(prompt->cmd->args[0]))
		g_exst = ft_exbuiltin(prompt, prompt->cmd);
	else if (!prompt->cmd->next)
		g_exst = onecmd_nobuilt(prompt);
	else
		g_exst = handle_cmds(prompt, &p);
	handle_stdio(&p, "RESTORE");
}
