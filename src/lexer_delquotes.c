/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_delquotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:37:01 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/19 18:31:29 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	upd_pos(char *s, int i, char c)
{
	while (s[i] && s[i] != c)
		i++;
	if (s[i] && s[i] == c)
		i++;
	return (i);
}

char	*copy_noquot(char *s, char *t)
{
	int		i;
	char	c;
	int		j;

	i = 0;
	j = 0;
	while (s[i] && s[i + 1])
	{
		if ((s[i] == DQUOTE || s[i] == SQUOTE) && s[i] == s[i + 1])
			i += 2;
		else if (s[i] == DQUOTE || s[i] == SQUOTE)
		{
			c = s[i];
			t[j++] = s[i++];
			while (s[i] && s[i] != c)
				t[j++] = s[i++];
			if (s[i] && s[i] == c)
				t[j++] = s[i++];
		}
		else
			t[j++] = s[i++];
	}
	t[j] = '\0';
	return (t);
}

char	*rm_consec_quotes(char *s, int del)
{
	char	*res;

	res = ft_calloc(sizeof(char), ft_strlen(s) - del + 1);
	if (!res)
		return (NULL);
	res = copy_noquot(s, res);
	return (res);
}

int	dbl_quot2del(char *p)
{
	int		res;
	int		i;
	char	c;

	res = 0;
	i = 0;
	while (p[i] && p[i + 1])
	{
		if ((p[i] == DQUOTE || p[i] == SQUOTE) && p[i] == p[i + 1])
		{
			res = res + 2;
			i = i + 2;
		}
		else if (p[i] == DQUOTE || p[i] == SQUOTE)
		{
			c = p[i];
			i++;
			if (p[i])
				i = upd_pos(p, i, c);
		}
		else
			i++;
	}
	return (res);
}

/* DELETES CONSECUTIVE QUOTES. Others are needed for variable replacement*/
char	**del_consec_quotes(char **s)
{
	int		i;
	int		char2del;
	char	**res;

	i = 0;
	res = ft_calloc(sizeof(char *), (dbl_len(s) + 1));
	if (!res)
		return (NULL);
	while (s[i])
	{
		char2del = dbl_quot2del(s[i]);
		if (ft_strlen(s[i]) > 1 && char2del != 0)
			res[i] = rm_consec_quotes(s[i], char2del);
		else
		{
			res[i] = ft_calloc(sizeof(char), ft_strlen(s[i]) + 1);
			if (!res[i])
				return (NULL);
			ft_strlcpy(res[i], s[i], ft_strlen(s[i]) + 1);
		}
		i++;
	}
	res[i] = NULL;
	free_all(s, dbl_len(s));
	return (res);
}
