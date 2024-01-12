/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:52:38 by erosas-c          #+#    #+#             */
/*   Updated: 2023/12/10 21:26:55 by erosas-c         ###   ########.fr       */
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

char	*rm_consec_quotes(char *s, int del)
{
	char	*res;
	int		i;
	char	c;
	int		j;

	i = 0;
	j = 0;
	res = malloc(sizeof(char) * ft_strlen(s) - del + 1);
	if (!res)
		return (NULL);
	while (s[i])
	{
		if ((s[i] == DQUOTE || s[i] == SQUOTE) && s[i] == s[i + 1])
			i += 2;
		else if (s[i] == DQUOTE || s[i] == SQUOTE)
		{
			c = s[i];
			res[j] = s[i];
			i++;
			j++;
			while (s[i] && s[i] != c)
			{
				res[j] = s[i];
				i++;
				j++;
			}
			if (s[i] && s[i] == c)
			{
				res[j] = c;
				i++;
				j++;
			}
		}
		else
		{
			res[i] = s[i];
			i++;
			j++;
		}
	}
	res[j] = '\0';
	return (res);
}

int	dbl_quot2del(char *p)
{
	int		res;
	int		i;
	char	c;

	res = 0;
	i = 0;
	while (p[i])
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
	res = malloc(sizeof(char *) * dbl_len(s) + 1);
	if (!res)
		return (NULL);
	while (s[i])
	{
		char2del = dbl_quot2del(s[i]);
		if (ft_strlen(s[i]) > 1 && char2del != 0)
			res[i] = rm_consec_quotes(s[i], char2del);
		else
		{
			res[i] = malloc(sizeof(char) * ft_strlen(s[i]) + 1);
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
