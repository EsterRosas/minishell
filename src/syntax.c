/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:47:13 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/17 19:14:05 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	unclosed_quotes(char *p)
{
	int		i;
	char	c;

	i = 0;
	while (p[i])
	{
		if (p[i] && (p[i] == SQUOTE || p[i] == DQUOTE))
		{
			c = p[i];
			i++;
			while (p[i] && p[i] != c)
				i++;
			if (!p[i])
				return (1);
		}
		i++;
	}
	return (0);
}

static int	check_quotes(char **lex)
{
	int	i;

	i = 0;
	while (lex[i])
	{
		if (ft_strchr(lex[i], SQUOTE) && unclosed_quotes(lex[i]))
		{
			handle_error_syn("syntax error near unexpected token", lex[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

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
	if (check_quotes(lex) == 1)
	{
		g_exst = 258;
		return (1);
	}
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
