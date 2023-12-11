/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 20:32:13 by erosas-c          #+#    #+#             */
/*   Updated: 2023/12/11 21:51:25 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**get_ptharr(t_envv *env_lst)
{
	char	**ptharr;

	while (env_lst && ft_strlen(env_lst->nm) != 4)
		env_lst = env_lst->next;
	if (env_lst && (ft_strlen(env_lst->nm) == 4)
		&& ft_strncmp(env_lst->nm, "PATH", 4) == 0)
		ptharr = ft_split(env_lst->val, ':');
	else
		return (NULL);
	return (ptharr);
}

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

t_cmd	fill_node(t_cmd s, char **lex, t_envv *env_lst)
{
	int	i;

	i = 0;
	while (lex[i] && lex[i][0] != '|')
	{
		if (ft_strlen(lex[i]) == 1 && (lex[i][0] == '<' || lex[i][0] == '>'))
		{
			if (lex[i][0] == '<')
				s.infile = assign_infile(lex[++i]);
			else
				s.outfile = assign_outfile(lex[++i]);
			i++;
		}
		else
		{
			s.args = fill_args(s.args, lex, i);
			i = i + dbl_len(s.args);
		}
		if (!is_builtin(s.args[0]) && s.args[0][0] != '/')
			s.full_path = fill_path(s.full_path, env_lst, s.args[0]);
	}
	return (s);
}

/* Takes the char** once it's been trimmed, subsplitted, expanded (~ to $HOME)
 * and with variables replaced and parses it into an array of several t_cmd
 * structs. (See ../inc/defines.h), and retuns the corresponding pointer.
 * NOTE: for the moment I'm only parsing ONE t_cmd (i.e., the array contains
 * always only one item).
 * TO_DO:
 * 1) Will need to add another t_cmd per pipe existing alone in the char**
 * 2) Will need to delete quotations (single and double) where needed
 */
t_cmd	*parse_lexed(char **lex, t_envv *env_lst)
{
	int		i;
	t_cmd	*res;
	int		cmd_n;

	i = -1;
	cmd_n = 1;
	while (++i < dbl_len(lex))
	{
		if (lex[i][0] == '|')
			cmd_n++;
	}
	res = malloc(sizeof(t_cmd) * cmd_n);
	if (!res)
		return (NULL);
	i = -1;
	while (++i < cmd_n)
	{
		res[i].args = malloc(sizeof(char *) * dbl_len(lex) + 1);
		res[i].full_path = NULL;
		res[i].infile = STDIN_FILENO;
		res[i].outfile = STDOUT_FILENO;
		res[i] = fill_node(res[i], lex, env_lst);
	}
	return (res);
}
