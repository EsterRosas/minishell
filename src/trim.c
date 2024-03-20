/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:42:52 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/20 17:20:45 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_upd_j(char *s, int j, int i)
{
	if (i == 0)
	{
		while (s[j] && s[j] != KSPACE)
			j++;
	}
	else if (s[j] == DQUOTE)
	{
		j++;
		while (s[j] && s[j] != DQUOTE)
			j++;
		if (s[j] == DQUOTE)
			j++;
	}
	else
	{
		j++;
		while (s[j] && s[j] != SQUOTE)
			j++;
		if (s[j] == SQUOTE)
			j++;
	}
	return (j);
}

static int	upd_jcount(int j, char *s)
{
	while (s[j])
	{
		while (s[j] && s[j] != KSPACE && s[j] != SQUOTE && s[j] != DQUOTE)
			j++;
		if (s[j] && s[j] == KSPACE)
			break ;
		else if (s[j])
		{
			if (s[j] && (s[j] == SQUOTE || s[j] == DQUOTE))  // while changed to if
				j = ft_upd_j(s, j, 1);
			if (s[j] && s[j] == KSPACE)
				break ;
			if (s[j])
				j++;
		}
	}
	return (j);
}

static int	ft_ptr_len(char *p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		while (p[i] && p[i] != KSPACE && p[i] != SQUOTE && p[i] != DQUOTE)
			i++;
		if (p[i] && p[i] == KSPACE)
			break ;
		else if (p[i])
		{
			while (p[i] && (p[i] == SQUOTE || p[i] == DQUOTE))
				i = ft_upd_j(p, i, 1);
			if (p[i] && p[i] == KSPACE)
				break ;
			if (p[i])
				i++;
		}
	}
	return (i);
}

int	ft_str_count(char *s)
{
	int	str_count;
	int	j;

	str_count = 0;
	j = 0;
	if (*s == '\0')
		return (0);
	while (s[j])
	{
		while (s[j] && s[j] == KSPACE)
			j++;
		if (s[j])
			str_count++;
		j = upd_jcount(j, s);
	}
	return (str_count);
}

/* Takes the line read from command line (user input) and splits it into
 * several char* (based on spaces not between single or double quotation
 * marks). Altogether form a **char which is the value returned.
 */
char	**cmdtrim(char *s)
{
	int		str_count;
	char	**res;
	int		n;
	char	*p;

//	p = NULL;
	n = 0;
	if (!s)
		return (NULL);
	str_count = ft_str_count(s);
	res = ft_calloc(sizeof(char *), str_count + 1);
	if (!res)
		return (NULL);
	while (n < str_count)
	{
		p = find_ptr(s, KSPACE);
		res[n] = ft_substr(p, 0, ft_ptr_len(p));
		if (res[n] == NULL)
			return (free_all(res, n));
		n++;
		s = s + (p - s) + ft_ptr_len(p);
	}
	res[n] = NULL;
	res = del_consec_quotes(res);
	return (res);
}
