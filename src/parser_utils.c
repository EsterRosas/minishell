/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 19:05:44 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/06 18:00:38 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
 *
 * PENDENT DE FER:
 * si un infile no existeix, independentment de l’ordre (posició entre els 
 * diversos infiles del t_cmd) >> ATUREM i saltem al següent t_cmd de la
 * llista (suposo que haure d’eliminar el node) i ja no el passem a l’executor
 */
void	assign_infile(char **lex, int i, t_cmd *s)
{
	int	fd;

	if (ft_strlen(lex[i - 1]) == 1 && is_lastfile(lex, i, lex[i - 1][0]))
	{
		if (access(lex[i], R_OK) == -1)
			printf("minishell: %s: %s\n", lex[i], strerror(errno));
		else
		{
			fd = open(lex[i], O_RDONLY);
			if (fd == -1)
				printf("minishell: %s: %s\n", lex[i], strerror(errno));
			else
				s->infile = fd;
		}
	}
	else if (ft_strlen(lex[i - 1]) == 2 && lex[i - 1][1] == '<')
		s->hdoc = process_hdoc(lex[i], is_lastfile(lex, i, '<'));
}

/* Defines the current lex position as output file only if it's the last one.
 * If it's not, it deletes its content (with O_TRUNC option).
 * If the open returns error 2 (non existing file), it creates it.
 *
 * Finally checks if the previous lex position was >> or >, so sets
 * the boolean s->append to true or false, respectively.
  */
void	assign_outfile(char **lex, int i, t_cmd *s)
{
	int	fd;

	if (!is_lastfile(lex, i, lex[i - 1][0]))
	{
		fd = open(lex[i], O_WRONLY | O_TRUNC);
		if (fd > 1)
			close (fd);
	}
	else
		s->outfile = open(lex[i], O_RDWR);
	if (s->outfile == -1 && errno == 2)
		s->outfile = open(lex[i], O_CREAT, 0600);
	else if (s->outfile == -1)
	{
		printf("minishell: %s: %s\n", lex[i], strerror(errno));
		//aqui hem de fer alguna cosa mes? pensar com i que hem de retornar
		//per si hem de saltar tot el cmd en aquest cas
	}
	i--;
	if (ft_strlen(lex[i]) == 2 && lex[i][1] == '>')
		s->append = true;
	else
		s->append = false;
}
