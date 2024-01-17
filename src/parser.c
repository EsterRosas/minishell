/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 20:32:13 by erosas-c          #+#    #+#             */
/*   Updated: 2024/01/17 12:41:54 by erosas-c         ###   ########.fr       */
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
			free(path);
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

	i = 0;
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

t_cmd	*fill_node(t_cmd *s, char **lex, t_envv *env_lst)
{
	int	i;

	i = 0;
	while (lex[i] && lex[i][0] != '|')
	{
		if (ft_strlen(lex[i]) == 1 && (lex[i][0] == '<' || lex[i][0] == '>'))
		{
			if (lex[i][0] == '<')
				s->infile = assign_infile(lex[++i]);
			else
				s->outfile = assign_outfile(lex[++i]);
			i++;
		}
		else
		{
			s->args = fill_args(s->args, lex, i);
			i = i + dbl_len(s->args);
		}
	//	del_end_quotes(s->args);
	}
	del_mid_quotes(s->args);
	if (!is_builtin(s->args[0]) && s->args[0][0] != '/')
		s->full_path = fill_path(s->full_path, env_lst, s->args[0]);
	return (s);
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
	res->full_path = NULL;
	res->infile = STDIN_FILENO;
	res->outfile = STDOUT_FILENO;
	res->next = NULL;
	res = fill_node(res, lex, env_lst);
	return (res);
}

/* Takes the char** once it's been trimmed, subsplitted, expanded (~ to $HOME)
 * and with variables replaced and parses it into an list of several t_cmd
 * structs. (See ../inc/defines.h), and retuns the corresponding pointer.
 * If the list has more than one element means they are separated by pipes
 * in the lexer / user input. It's important to have this in mind for the
 * executor
 * STILL TO DO:
 * 1) IMPORTANT NOTE: For the moment it does't manage neither << nor >>
 */
t_cmd	*get_cmdlst(char **lex, t_envv *env_lst)
{
	t_cmd	*cmdlst;
	int		cmd_n;
	int		i;

	cmd_n = 1;
	i = 0;
	cmdlst = get_cmd(lex, env_lst);
	while (++i < dbl_len(lex))
	{
		if (lex[i][0] == '|')
			cmd_n++;
	}
	if (cmd_n > 1)
		fill_cmdlst(lex, env_lst, cmdlst, cmd_n);
	free_all(lex, dbl_len(lex));
	return (cmdlst);
}
