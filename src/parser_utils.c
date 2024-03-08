/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 19:05:44 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/07 12:09:13 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*path2cmd(char *arg)
{
	int		i;

	i = ft_strlen(arg) - 1;
	while (i >= 0 && arg[i] != '/')
		i--;
	return (ft_substr(arg, i + 1, ft_strlen(arg) - 1));
}

int	is_inpath(char *s, t_envv *env)
{
	char	**pth_arr;
	char	**aux;
	int		i;
	char	*folder;

	i = ft_strlen(s) - 1;
	while (i >= 0 && s[i] != '/')
		i--;
	folder = ft_substr(s, 0, i);
	pth_arr = get_ptharr(env);
	aux = pth_arr;
	i = -1;
	while (aux[++i])
	{
		if (ft_strcmp(aux[i], folder) == 0)
			return (1);
	}
	return (0);
}

int	is_lastfile(char **lex, int i, char c)
{
	while (lex[i] && lex[i][0] != '|' && lex[i][0] != c)
		i++;
	if (!lex[i] || lex[i][0] == '|')
		return (1);
	return (0);
}

/* CAT: cat < . si que ha de ser "." arg que se li passi a exec
 * EN CANVI, FIND: es queda com a infile o el que sigui pero no com a arg.
 */
int	assign_infile(char **lex, int i, t_cmd *s)
{
	int	fd;

	if (ft_strlen(lex[i - 1]) == 1) //&& is_lastfile(lex, i, lex[i - 1][0]))
	{
		/*if (access(lex[i], R_OK) == -1)
		{
			handle_error(lex[i], strerror(errno));
			return (-1);
		}
		else
		{*/
			fd = open(lex[i], O_RDONLY);
			if (fd == -1)
			{
				handle_error(lex[i], strerror(errno));
				return (-1);
			}
			else
				s->infile = fd;
	//	}
		return (0);
	}
	else if (ft_strlen(lex[i - 1]) == 2 && lex[i - 1][1] == '<')
		s->infile = process_hdoc(lex[i], is_lastfile(lex, i, '<'));
	return (0);
}

/* Defines the current lex position as output file only if it's the last one.
 * If it's not, it deletes its content (with O_TRUNC option).
 * If the open returns error 2 (non existing file), it creates it.
 *
 * First it checks if the previous lex position was >> or >, so to open the
 * outfile in append mode or not.
 */
int	assign_outfile(char **lex, int i, t_cmd *s)
{
//	int		fd;
	bool	append;

	append = false;
	if (ft_strlen(lex[i - 1]) == 2 && lex[i - 1][1] == '>')
		append = true;
/*	if (!is_lastfile(lex, i, lex[i - 1][0]) && append == false)
	{
		fd = open(lex[i], O_WRONLY | O_TRUNC);
		if (fd > 1)
			close (fd);
	}*/
	if (append == false)
		s->outfile = open(lex[i], O_WRONLY | O_TRUNC);
	else
		s->outfile = open(lex[i], O_WRONLY | O_APPEND, 0600);
	if (s->outfile == -1 && errno == 2)
		s->outfile = open(lex[i], O_CREAT | O_WRONLY, 0600);
	else if (s->outfile == -1)
	{
		handle_error(lex[i], strerror(errno));
		return (-1);
	}
	return (0);
}
