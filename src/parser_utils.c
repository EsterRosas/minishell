/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 19:05:44 by erosas-c          #+#    #+#             */
/*   Updated: 2024/01/25 21:23:42 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*int	is_lastfile(char **lex, int i, char c)
{


}*/

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
 * NOTA IMPORTANT: si troba el fitxer output (tant > com >>) pero no es el
 * darrer, no l'envia com a outfile, pero si que n'esborra el contingut!!!
 * A MESURA QUE PASSEM, sempre que no sigui el darrer, n'hem d'esborrar el
 * contingut. A la carpeta Tests hi tinc la funcio feta per fer-ho:
 * delete_file_content.c. Haurem de simular ftruncate function. 
 * CREC QUE HO PODEM FER SUBSTITUINT CADA caracter del fitxer (a traves de
 * get_next_line o d'algun read o aixi i posant en comptes de que hi ha el
 * '\0' a cada caracter. Potser simplement posant '\0' en el primer caracter?
 * AMB UN SIMPLE WRITE??
 */
void	assign_outfile(char **lex, int i, t_cmd *s)
{
//	if (!is_lastfile

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
