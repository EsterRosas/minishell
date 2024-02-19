/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 19:05:44 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/19 21:27:28 by erosas-c         ###   ########.fr       */
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
	{
		char buffer[10];
		s->infile = process_hdoc(lex[i], is_lastfile(lex, i, '<'));
		printf("s->infile: %i\n", s->infile);
		int i = -1;
		while (++i < 10)
		{
			read(s->infile, &buffer[i], 1);
			i++;
		}
		printf("buffer: %s\n", buffer);
		close(s->infile);
	}
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

int	is_env(char *s)
{
	int	i;

	i = 0;
	if (ft_strlen(s) != 3)
		return (0);
	else if (s[0] != 'e' && s[0] != 'E')
		return (0);
	else if (s[1] != 'n' && s[1] != 'N')
		return (0);
	else if (s[2] != 'v' && s[2] != 'V')
		return (0);
	return (1);
}
