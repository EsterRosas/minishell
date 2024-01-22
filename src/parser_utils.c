/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 19:05:44 by erosas-c          #+#    #+#             */
/*   Updated: 2024/01/22 21:11:48 by erosas-c         ###   ########.fr       */
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
		s->infiles[0].path = lex[i + 1];
		if (ft_strlen(lex[i]) == 2 && lex[i][1] == lex[i][0])
			s->infiles[0].hdoc = true;
		else
			s->infiles[0].hdoc = false;
		s->infiles[1].path = NULL;
	}
	else
	{
		n = 0;
		while (s->infiles[n].path)
			n++;
		s->infiles[n].path = lex[i + 1];
		if (ft_strlen(lex[i]) == 2 && lex[i][1] == lex[i][0])
			s->infiles[n].hdoc = true;
		else
			s->infiles[n].hdoc = false;
		s->infiles[n + 1].path = NULL;
	}
}

/* NOTE: If the file cannot be opened, it doesn't get to the line where it
 * checks whether its append instead of simple redirection
 * if the file doesn't exist yet, now its returning the error, but we should
 * create it instead
 */
int	assign_outfile(char **lex, int i, bool *append)
{
	int	fd;

	fd = open(lex[i], O_RDWR);
	if (fd == -1)
	{
		printf("Error opening file %s\n", lex[i]);
		return (-1);
	}
	i--;
	if (ft_strlen(lex[i]) == 2 && lex[i][1] == '>')
		*append = true;
	return (fd);
}
