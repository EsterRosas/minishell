/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 20:32:13 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/06 20:55:16 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*fill_path(char *path, t_envv *env_lst, char *first_arg)
{
	char	**path_vls;
	int		i;
	char	*aux;

	i = 0;
	path_vls = get_ptharr(env_lst);
	while (path_vls[i])
	{
		aux = ft_strjoin(path_vls[i], "/");
		path = ft_strjoin(aux, first_arg);
		free(aux);
		if (access(path, F_OK) == 0)
			break ;
		else
		{
			if (path)
				free(path);
			path = NULL;
			i++;
		}
	}
	free_all(path_vls, dbl_len(path_vls));
	return (path);
}

char	**fill_args(char **args, char **lex, int lex_pos)
{
	int	i;
	int	j;

	i = dbl_len(args);
	j = 0;
	while (lex[lex_pos] && !is_sep(lex[lex_pos][0]))
	{
		args[i] = malloc(sizeof(char) * ft_strlen(lex[lex_pos]) + 1);
		if (!args[i])
			return (NULL);
		while (lex[lex_pos][j])
		{
			args[i][j] = lex[lex_pos][j];
			j++;
		}
		args[i][j] = '\0';
		i++;
		lex_pos++;
		j = 0;
	}
	args[i] = NULL;
	return (args);
}

/* NOTA IMPORTANT: heredoc te els seus propis
 * senyals, pq si estem a mig "demanar input heredoc a usuari", si es fa Ctr+C
 * o altres, surt del heredoc, pero no del minishell, per aixo heredoc s'ha
 * d'executar en un proces a part (child).
 */
int	fill_node(t_cmd *s, char **lex)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (lex[i] && lex[i][0] != '|')
	{
		if (lex[i][0] == '<' || lex[i][0] == '>')
		{
			if (lex[i][0] == '>')
				assign_outfile(lex, ++i, s);
			else if (lex[i][0] == '<')
			{
				if (assign_infile(lex, ++i, s) == -1)
					return (-1);
			}
			i++;
		}
		else
		{
			s->args = fill_args(s->args, lex, i);
			i = i + dbl_len(s->args) - len;
			len = dbl_len(s->args);
		}
	}
	del_mid_quotes(s->args);
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
	res->append = false;
	res->next = NULL;
	res->hdoc = NULL;
	if (fill_node(res, lex) == -1)
		return (NULL);
	else if (!is_builtin(res->args[0]) && res->args[0][0] != '/')
		res->full_path = fill_path(res->full_path, env_lst, res->args[0]);
	return (res);
}

/* Takes the char** once it's been trimmed, subsplitted, expanded (~ to $HOME)
 * and with variables replaced and parses it into an list of several t_cmd
 * structs. (See ../inc/defines.h), and retuns the corresponding pointer.
 * If the list has more than one element means they are separated by pipes
 * in the lexer / user input. It's important to have this in mind for the
 * executor
 * STILL TO DO:
 * 2) PRIMER CAL QUE MIREM quina es l'ordre
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
	t_cmd	*cmdlst;
	int		cmd_n;
	int		i;
	char	**lexed;

	cmd_n = 1;
	i = 0;
	lexed = repl_var(cmdexpand(cmdsubsplit(cmdtrim(line))), env_lst);
	cmdlst = get_cmd(lexed, env_lst);
	while (++i < dbl_len(lexed))
	{
		if (lexed[i][0] == '|')
			cmd_n++;
	}
	/*if (!cmdlst)
	{
		ft_skipnode(lex...///completar - REINICIALITZAR DADES NODE I MOURE POSICIO al PIPE + 1
		cmd_n--;
	}*/
	if (cmd_n > 1)
		fill_cmdlst(lexed, env_lst, cmdlst, cmd_n);
	free_all(lexed, dbl_len(lexed));
	return (cmdlst);
}
