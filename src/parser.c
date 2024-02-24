/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 20:32:13 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/23 20:21:30 by erosas-c         ###   ########.fr       */
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
	int		i;
	int		j;

	i = dbl_len(args);
	j = -1;
	while (lex[lex_pos] && !is_sep(lex[lex_pos][0]))
	{
		if (i == 0 && lex[lex_pos][0] == '/' && access(lex[lex_pos], F_OK) == 0)
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
int	fill_node(t_cmd *s, char **lex)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (lex[i] && lex[i][0] != '|')
	{
		if ((lex[i][0] == '<' && assign_infile(lex, i + 1, s) == -1) ||
			(lex[i][0] == '>' && assign_outfile(lex, i + 1, s) == -1))
			return (-1);
		else if (lex[i][0] == '<' || lex[i][0] == '>')
			i += 2;
		else
		{
			s->args = fill_args(s->args, lex, i);
			i = i + dbl_len(s->args) - len;
			len = dbl_len(s->args);
		}
	}
	del_quotes(s->args);
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
	if (fill_node(res, lex) == -1)
		return (NULL);
/*	if (res->args)
		upd_underscore_var(*/
	else if (!is_builtin(res->args[0]) && res->args[0][0] != '/')
		res->full_path = fill_path(res->full_path, env_lst, res->args[0]);
	return (res);
}
