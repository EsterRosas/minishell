/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 19:05:44 by erosas-c          #+#    #+#             */
/*   Updated: 2024/01/26 13:54:29 by erosas-c         ###   ########.fr       */
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

void	assign_infile(char **lex, int i, t_cmd *s)
{
	if (s->infile > 1)
		close(s->infile);
	s->infile = open(lex[i], O_RDONLY);
	if (s->infile == -1)
		return;
}

/* Defines the current lex position as output file only if it's the last one.
 * If it's not, it deletes its content (with O_TRUNC option).
 * If the open returns error 2 (non existing file), it cretes it.
 *
 * Finally checks if the previous lex position was >> or >, so sets
 * the boolean s->append to true or false, respectively.
 *
 * Si el problema no es que no existeix, caldra fer una altra cosa!!!!!
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
	if (s->outfile == -1 && errno == 2) // 2 es quan no el troba
		s->outfile = open(lex[i], O_CREAT, 0600);
	else
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
