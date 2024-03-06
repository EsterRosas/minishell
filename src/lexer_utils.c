/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:52:38 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/26 12:58:18 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_syntax(char **lex)
{
	int	i;

	i = -1;
	while (lex[++i] && lex[i + 1])
	{
		if (lex[i + 1] && (lex[i][0] == '|' && lex[i + 1][0] == '|'))
		{
			only_msg_err("syntax error near unexpected token `||'");
			g_exst = 258;
			return (1);
		}
	}
	if (lex[0][0] == '|' || lex[dbl_len(lex) - 1][0] == '|')
	{
		only_msg_err("syntax error near unexpected token `|'");
		g_exst = 258;
		return (1);
	}
	return (0);
}

char	*last_spl(char *tr, int l)
{
	char	*sp;

	if (tr[l - 1] == '|' || (tr[l - 1] != tr[l - 2]))
		sp = ft_substr(tr, 0, l - 1);
	else
		sp = ft_substr(tr, 0, l - 2);
	return (sp);
}

char	*first_spl(char *tr)
{
	char	*sp;

	if (tr[0] == '|' || (tr[0] != tr[1]))
		sp = ft_substr(tr, 0, 1);
	else
		sp = ft_substr(tr, 0, 2);
	return (sp);
}

int	is_sep(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int	count_new_ptrs(char **s)
{
	int	num;
	int	i;

	num = 0;
	i = 0;
	while (s[i])
	{
		if ((!ft_strchr(s[i], '<') && !ft_strchr(s[i], '>')
				&& !ft_strchr(s[i], '|')) || only_sep(s[i]))
			i++;
		else
		{
			num++;
			i++;
		}
	}
	return (num);
}
