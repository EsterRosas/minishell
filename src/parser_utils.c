/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 19:05:44 by erosas-c          #+#    #+#             */
/*   Updated: 2024/01/23 11:00:37 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


int	ct_files(char c, char **lex, int i)
{
	int	ct;

	ct = 0;
	while (lex[i] && lex[i][0] != '|')
	{
		if (lex[i][0] == c)
			ct++;
		i++;
	}
	return (ct);
}
void	assign_infile(t_cmd *s, char **lex, int i)
{
	int n;

	n = 0;
	if (s->infiles == NULL)
	{
		n = ct_files('<', lex, i);
		s->infiles = malloc(sizeof(t_in) * n + 1);
		if (!s->infiles)
			return;
		s->infiles[0].file = ft_strcp(lex[i + 1]);
		if (ft_strlen(lex[i]) == 2 && lex[i][1] == lex[i][0])
			s->infiles[0].hdoc = true;
		else
			s->infiles[0].hdoc = false;
		s->infiles[1].file = NULL;
	}
	else
	{
		n = 0;
		while (s->infiles[n].file)
			n++;
		s->infiles[n].file = ft_strcp(lex[i + 1]);
		if (ft_strlen(lex[i]) == 2 && lex[i][1] == lex[i][0])
			s->infiles[n].hdoc = true;
		else
			s->infiles[n].hdoc = false;
		s->infiles[n + 1].file = NULL;
	}
}

/* NOTE: If the file cannot be opened, it doesn't get to the line where it
 * checks whether its append instead of simple redirection
 * if the file doesn't exist yet, now its returning the error, but we should
 * create it instead
 */
void	assign_outfile(t_cmd *s, char **lex, int i)
{

	int n;
//fent aquest a mitges
	n = 0;
	if (s->infiles == NULL)
	{
		n = ct_files('<', lex, i);
		s->infiles = malloc(sizeof(t_in) * n + 1);
		if (!s->infiles)
			return;
		s->infiles[0].file = ft_strcp(lex[i + 1]);
		if (ft_strlen(lex[i]) == 2 && lex[i][1] == lex[i][0])
			s->append = true;
		else
			s->append = false;
		s->outfiles[1] = NULL;
	}
	else
	{
		n = 0;
		while (s->infiles[n].file)
			n++;
		s->infiles[n].file = ft_strcp(lex[i + 1]);
		if (ft_strlen(lex[i]) == 2 && lex[i][1] == lex[i][0])
			s->infiles[n].hdoc = true;
		else
			s->infiles[n].hdoc = false;
		s->infiles[n + 1].file = NULL;
	}
}
