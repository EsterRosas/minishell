/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:47:13 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/10 18:44:45 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	check_more(char **lex)
{
	int	i;

	i = -1;
	while (lex[++i] && lex[i + 1])
	{
		if (lex[i + 1] && (lex[i][0] == '|' || lex[i][0] == '>')
			&& lex[i + 1][0] == '|')
		{
			only_msg_err("syntax error near unexpected token `|'");
			break ;
		}
		else if (lex[i + 1] && (lex[i][0] == '>' && lex[i + 1][0] == '<'))
		{
			only_msg_err("syntax error near unexpected token `<'");
			break ;
		}
	}
	if (i + 1 != dbl_len(lex))
		return (1);
	return (0);
}

int	check_syntax(char **lex)
{
	if (check_more(lex) == 1)
	{
		g_exst = 258;
		return (1);
	}
	if (lex[dbl_len(lex) - 1][0] == '>' || lex[dbl_len(lex) - 1][0] == '<')
	{
		only_msg_err("syntax error near unexpected token `newline'");
		g_exst = 258;
		return (1);
	}
	else if ((lex[0][0] == '|' || lex[dbl_len(lex) - 1][0] == '|')
		|| (lex[0][0] == '<' && lex[1][0] && lex[1][0] == '|'))
	{
		only_msg_err("syntax error near unexpected token `|'");
		g_exst = 258;
		return (1);
	}
	return (0);
}
