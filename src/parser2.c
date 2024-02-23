/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 20:32:13 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/23 19:07:21 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**get_ptharr(t_envv *env_lst)
{
	char	**ptharr;

	ptharr = NULL;
	while (env_lst && ft_strcmp(env_lst->nm, "PATH") != 0)
		env_lst = env_lst->next;
	if (env_lst && ft_strcmp(env_lst->nm, "PATH") == 0)
		ptharr = ft_split(env_lst->val, ':');
	return (ptharr);
}

void	cmdlst_addback(t_cmd *cmdlst, t_cmd *new)
{
	if (cmdlst == 0)
		cmdlst = new;
	else
	{
		if (!cmdlst)
			return ;
		while (cmdlst->next)
			cmdlst = cmdlst->next;
	}
	cmdlst->next = new;
}

/* Takes the char** once it's been trimmed, subsplitted, expanded (~ to $HOME)
 * and with variables replaced and parses it into an list of several t_cmd
 * structs. (See ../inc/defines.h), and retuns the corresponding pointer.
 * If the list has more than one element means they are separated by pipes
 * in the lexer / user input. It's important to have this in mind for the
 * executor
 * 
 * ATENCIO: need to create a grid with all possible cmds to know what they
 * receive and so know if execve receives infile as arg or as input file.
 *
 * NOTA:
 * quan no es builtin execve sembla que no gestiona Command
 * “bash: un: command not found”, per tant haurem de fer que ho imprimeixi
 * quan agafem ruta  d’exec (no builtin) pero path = NULL
 */
t_cmd	*get_cmdlst(char *line, t_envv *env_lst)
{
	t_cmd	*res;
	char	**lex;
	t_cmd	*new;
	int		i;

	lex = repl_var(cmdexpand(cmdsubsplit(cmdtrim(line))), env_lst);
	res = NULL;
	i = 0;
	while (lex[i])
	{
		new = get_cmd(&lex[i], env_lst);
		if (new && res)
			cmdlst_addback(res, new);
		else if (new)
			res = new;
		while (lex[i] && lex[i][0] != '|')
			i++;
		if (lex[i] && lex[i][0] == '|')
			i++;
	}
	free_all(lex, dbl_len(lex));
	return (res);
}

void	free_cmdlist(t_cmd *head)
{
	t_cmd	*current;
	t_cmd	*nextnode;

	current = head;
	while (current)
	{
		nextnode = current->next;
		free_all(current->args, dbl_len(current->args));
		if (current->full_path)
			free(current->full_path);
		free(current);
		current = nextnode;
	}
}

void	free_envlist(t_envv *head)
{
	t_envv	*current;
	t_envv	*nextnode;

	current = head;
	while (current)
	{
		nextnode = current->next;
		if (current->nm)
			free(current->nm);
		if (current->val)
			free(current->val);
		free(current);
		current = nextnode;
	}
}
