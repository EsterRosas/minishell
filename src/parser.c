/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 20:32:13 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/12 17:54:15 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	get_node(t_cmd *s, char **lex, t_envv *env)
{
	int		i;
	int		len;
	t_iptrs	*iptrs;

	i = 0;
	len = 0;
	iptrs = malloc(sizeof(t_iptrs));
	if (!iptrs)
		return (0);
	iptrs->i = &i;
	iptrs->len = &len;
	while (lex[i] && lex[i][0] != '|')
	{
		if (stop_case_cat(s, lex[i]))
			break ;
		else if (upd_node(s, lex, env, iptrs) == -1)
		{
			free(iptrs);
			return (-1);
		}
	}
	free(iptrs);
	return (0);
}

/* * If there's an error in some input or output file returns -1 so the node can
 * be skipped in the list. Same if no item is added in the args, which means
 * no command has been input by the user.
 */
static int	fill_node(t_cmd *s, char **lex, t_envv *env)
{
	s->args = malloc(sizeof(char *) * dbl_len(lex) + 1);
	if (!s->args)
		return (-1);
	s->args[0] = NULL;
	if (get_node(s, lex, env) == -1)
		return (-1);
	if (!s->args && s->outfile == 1 && s->infile == 0)
		return (-1);
	if (!is_inenvlst("PWD", env) && dbl_len(s->args) > 1
		&& ft_strcmp(s->args[0], "cd") == 0 && s->args[1][0] == '.')
	{
		if (ft_strlen(s->args[1]) == 1)
			s->args[1] = dot2path(s->args[1]);
		else if (ft_strlen(s->args[1]) == 2 && s->args[1][1] == '.')
			s->args[1] = dots2path(s->args[1]);
	}
	return (0);
}

t_cmd	*get_cmd(char **lex, t_envv *env_lst)
{
	t_cmd	*res;
	int		test;

	test = 0;
	res = malloc(sizeof(t_cmd));
	if (!res)
		return (NULL);
	res->full_path = NULL;
	res->infile = STDIN_FILENO;
	res->outfile = STDOUT_FILENO;
	res->next = NULL;
	test = fill_node(res, lex, env_lst);
	if (test == -1)
	{
		free_all(res->args, dbl_len(res->args));
		free(res);
		return (NULL);
	}
	else if (!res->full_path && res->args[0] && res->args[0][0] != '/'
		&& !is_builtin(res->args[0]) && ft_strcmp(res->args[0], "") != 0)
		res->full_path = fill_path(res->full_path, env_lst, res->args[0]);
	return (res);
}

static t_cmd	*get_list(char **lex, t_cmd *res, t_envv *env_lst)
{
	int		i;
	t_cmd	*new;

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
	return (res);
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

	res = NULL;
	lex = repl_var(cmdexpand(cmdsubsplit(cmdtrim(line))), env_lst);
	if (check_syntax(lex) == 1)
	{
		free_all(lex, dbl_len(lex));
		return (NULL);
	}
	res = get_list(lex, res, env_lst);
	if (res)
		del_quotes(res->args);
	free_all(lex, dbl_len(lex));
	return (res);
}
