/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 20:32:13 by erosas-c          #+#    #+#             */
/*   Updated: 2023/12/12 20:33:40 by erosas-c         ###   ########.fr       */
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
		del_all_quotes(s->args);
		if (!is_builtin(s->args[0]) && s->args[0][0] != '/')
			s->full_path = fill_path(s->full_path, env_lst, s->args[0]);
	}
	return (s);
}

/* Takes the char** once it's been trimmed, subsplitted, expanded (~ to $HOME)
 * and with variables replaced and parses it into an array of several t_cmd
 * structs. (See ../inc/defines.h), and retuns the corresponding pointer.
 * NOTE: for the moment I'm only parsing ONE t_cmd (i.e., the array contains
 * always only one item). PROBABLY I WILL CHANGE THIS INTO A LIST. NOT SURE
 * If so, need to redo free and other functions related to this array/list.
 *
 * TO_DO:
 * 1) Will need to add another t_cmd per pipe existing alone in the char**
 * But need to review notes and doc on how pies work. David, maybe you will
 * know all of this better...
 * 2) Will need to delete quotations (single and double) where needed
 * 3) For the moment it does't manage neither << nor >>
 */
t_cmd	*get_cmd(char **lex, t_envv *env_lst)
{
	t_cmd	*res;
	
	res = malloc(sizeof(t_cmd));
	if (!res)
		return (NULL);
/*	while (++i < cmd_n)
	{*/
		res->args = malloc(sizeof(char *) * dbl_len(lex) + 1);
		res->full_path = NULL;
		res->infile = STDIN_FILENO;
		res->outfile = STDOUT_FILENO;
		res->next = NULL;
		res = fill_node(res, lex, env_lst);
//	}
	return (res);
}

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
	return (cmdlst);
}
