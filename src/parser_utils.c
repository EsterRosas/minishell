/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 19:05:44 by erosas-c          #+#    #+#             */
/*   Updated: 2024/01/24 18:09:57 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	assign_infile(char **lex, int i, t_cmd *s)
{
	if (s->infile > 1)
		close(s->infile);
	s->infile = open(lex[i], O_RDONLY);
	if (s->infile == -1)
		return;
}

/* Defines the current lex position as output file. Before, in case there
 * has been assigned a previous output file, it is closed.
 * Finally checks if the previous lex position was >> or >, so sets
 * the boolean s->append to true or false, respectively.
 * ATENCIO: ara mateix el crea en cas que no el pugui obrir,
 * EN REALITAT sera NOMES SI EL PROBLEMA (ERROR) es que no existeix.
 *
 * Si el problema es de permisos, caldra fer una altra cosa!!!!!
 *
 * NOTA IMPORTANT: si troba el fitxer output pero no es el darrer, no l'envia
 * com a outfile, pero si que n'esborra el contingut!!!
 */
void	assign_outfile(char **lex, int i, t_cmd *s)
{
	if (s->outfile > 1)
		close(s->outfile);
	s->outfile = open(lex[i], O_RDWR);
	if (s->outfile == -1)
		s->outfile = open(lex[i], O_CREAT, 0600);
	i--;
	if (ft_strlen(lex[i]) == 2 && lex[i][1] == '>')
		s->append = true;
	else
		s->append = false;
}
