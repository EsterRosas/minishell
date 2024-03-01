/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 19:05:44 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/01 21:39:17 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_wc_opt(char *l)
{
	if (ft_strcmp(l, "-l") == 0)
		return (1);
	else if (ft_strcmp(l, "-w") == 0)
		return (1);
	else if (ft_strcmp(l, "-c") == 0)
		return (1);
	return (0);
}

int	stop_case_catwc(t_cmd *s, char *l)
{
	printf("enters stop case\n");
	if (s->args[0] && s->infile != 0)
	{
		if (ft_strcmp(s->args[0], "cat") == 0
			|| ft_strcmp(s->args[0], "wc") == 0)
		{	
			if (s->args[1] || !is_wc_opt(l))
			return (1);
		}
	}
	return (0);
}

char	*path2cmd(char *arg)
{
	int		i;

	i = ft_strlen(arg) - 1;
	while (i >= 0 && arg[i] != '/')
		i--;
	return (ft_substr(arg, i + 1, ft_strlen(arg) - 1));
}

int	is_lastfile(char **lex, int i, char c)
{
	while (lex[i] && lex[i][0] != '|' && lex[i][0] != c)
		i++;
	if (!lex[i] || lex[i][0] == '|')
		return (1);
	return (0);
}

/* CAT: cat < . si que ha des er "." arg que se li passi a exec
 * EN CANVI, FIND: es queda com a infile o el que sigui pero no com a arg.
 */
int	assign_infile(char **lex, int i, t_cmd *s)
{
	int	fd;

	if (ft_strlen(lex[i - 1]) == 1 && is_lastfile(lex, i, lex[i - 1][0]))
	{
		if (access(lex[i], R_OK) == -1)
		{
			printf("minishell: %s: %s\n", lex[i], strerror(errno));
			return (-1);
		}
		else
		{
			fd = open(lex[i], O_RDONLY);
			if (fd == -1)
			{
				printf("minishell: %s: %s\n", lex[i], strerror(errno));
				return (-1);
			}
			else
				s->infile = fd;
		}
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
	int		fd;
	bool	append;

	append = false;
	if (ft_strlen(lex[i - 1]) == 2 && lex[i - 1][1] == '>')
		append = true;
	if (!is_lastfile(lex, i, lex[i - 1][0]) && append == false)
	{
		fd = open(lex[i], O_WRONLY | O_TRUNC);
		if (fd > 1)
			close (fd);
	}
	else if (append == false)
		s->outfile = open(lex[i], O_WRONLY | O_TRUNC);
	else
		s->outfile = open(lex[i], O_WRONLY | O_APPEND, 0600);
	if (s->outfile == -1 && errno == 2)
		s->outfile = open(lex[i], O_CREAT | O_WRONLY, 0600);
	else if (s->outfile == -1)
	{
		printf("minishell: %s: %s\n", lex[i], strerror(errno));
		return (-1);
	}
	return (0);
}
