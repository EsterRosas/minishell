/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 20:32:13 by erosas-c          #+#    #+#             */
/*   Updated: 2024/01/21 21:17:07 by erosas-c         ###   ########.fr       */
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

/* I think I have to redo this ft cause takes i not as expected*/
char	**fill_args(char **args, char **lex, int lex_pos)
{
	int	i;
	int	j;

	i = dbl_len(args);
	printf("enter FILL_ARGS i = dbl_len(args): %i\n", i);
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
	args[i] = NULL; //potser aixo ho he de fer mes tard, pq si no no puc afegir elements, no?
	i = 0;
	while (args[i])
	{
		printf("args[%i]: %s\n", i, args[i]);
		i++;
	}
	return (args);
}

/*(ft_strlen(lex[i]) == 1 &&*/
t_cmd	*fill_node(t_cmd *s, char **lex)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (lex[i] && lex[i][0] != '|')
	{
		printf("enters FILL_NODE while, lex[%i]: %s\n", i, lex[i]);
		if (lex[i][0] == '<' || lex[i][0] == '>')
		{
			printf("enterS IF 1 FILL_NODE\n");
			if (lex[i][0] == '<')
				s->infile = assign_infile(lex[++i]);
			else
			{
				printf("enters ELSE FILL_NODE\n");
				s->outfile = assign_outfile(lex, ++i, &s->append);
				printf("ELSE fill_node outfile: %i\n", s->outfile);
			}
			i++;
		}
		else
		{
			printf("enters ELSE 2 fill_node\n");
			s->args = fill_args(s->args, lex, i);
			printf("ELSE 2 fill_node (parser), i: %i, dbl_len(s->args): %i, len: %i\n", i, dbl_len(s->args), len);
			i = i + dbl_len(s->args) - len;
			printf("i value after FILL_ARGS in ELSE 2 in fill_node (parser.c): %i\n", i);
			len = dbl_len(s->args);
		}
	}
	del_mid_quotes(s->args);
	return (s);
}

t_cmd	*get_cmd(char **lex, t_envv *env_lst)
{
	t_cmd	*res;

	int i = 0;
	while (lex[i])
	{
		printf("GET_CMD lex[%i]: %s\n", i, lex[i]);
		i++;
	}
	res = malloc(sizeof(t_cmd));
	if (!res)
		return (NULL);
	printf("after MALLOC GET_CMD\n");
	res->args = malloc(sizeof(char *) * dbl_len(lex) + 1);
	if (!res->args)
		return (NULL);
	res->full_path = NULL;
	res->infile = STDIN_FILENO;
	res->outfile = STDOUT_FILENO;
	res->append = false;
	res->next = NULL;
	res = fill_node(res, lex);
	if (!is_builtin(res->args[0]) && res->args[0][0] != '/')
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
