/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 20:32:13 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/06 17:52:23 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**fill_args(char **args, char **lex, int lex_pos, t_envv *env)
{
	int		i;
	int		j;

	i = dbl_len(args);
	j = -1;
	while (lex[lex_pos] && !is_sep(lex[lex_pos][0]))
	{
		if (i == 0 && lex[lex_pos][0] == '/' && access(lex[lex_pos], F_OK) == 0
			&& is_inpath(lex[lex_pos], env))
			args[i] = path2cmd(lex[lex_pos]);
		else
		{
			args[i] = malloc(sizeof(char) * ft_strlen(lex[lex_pos]) + 1);
			if (!args[i])
				return (NULL);
			while (lex[lex_pos][++j])
				args[i][j] = lex[lex_pos][j];
			args[i][j] = '\0';
		}
		i++;
		lex_pos++;
		j = -1;
	}
	args[i] = NULL;
	return (args);
}

/* * If there's an error in some input or output file returns -1 so the node can
 * be skipped in the list. Same if no item is added in the args, which means
 * no command has been input by the user.
 */
int	fill_node(t_cmd *s, char **lex, t_envv *env)
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
		else if ((lex[i][0] == '<' && assign_infile(lex, i + 1, s) == -1) ||
			(lex[i][0] == '>' && assign_outfile(lex, i + 1, s) == -1))
		{
			g_exst = 1;
			return (-1);
		}
		else if (lex[i][0] == '<' || lex[i][0] == '>')
			i += 2;
		else
		{
			s->args = add_arg(s->args, lex, iptrs, env);
			free(iptrs);
		}
	}
	if (!s->args[0])
		return (-1);
	return (0);
}

t_cmd	*get_cmd(char **lex, t_envv *env_lst)
{
	t_cmd	*res;

	res = malloc(sizeof(t_cmd));
	if (!res)
		return (NULL);
	res->args = malloc(sizeof(char *) * dbl_len(lex) + 1);
	if (!res->args)
		return (NULL);
	res->args[0] = NULL;
	res->full_path = NULL;
	res->infile = STDIN_FILENO;
	res->outfile = STDOUT_FILENO;
	res->next = NULL;
	if (fill_node(res, lex, env_lst) == -1)
		return (NULL);
	else if (!is_builtin(res->args[0]) && res->args[0][0] != '/'
		&& ft_strcmp(res->args[0], "") != 0)
		res->full_path = fill_path(res->full_path, env_lst, res->args[0]);
	return (res);
}

t_cmd	*get_list(char **lex, t_cmd *res, t_envv *env_lst)
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
	if (check_syntax(lex))
	{
		free_all(lex, dbl_len(lex));
		return (NULL);
	}
	res = get_list(lex, res, env_lst);
	del_quotes(res->args);
	free_all(lex, dbl_len(lex));
	return (res);
}
