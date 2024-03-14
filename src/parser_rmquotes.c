/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_rmquotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:52:06 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/10 18:46:50 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*cp_woquotes(char *s, char *t)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] != SQUOTE && s[i] != DQUOTE)
			t[j++] = s[i++];
		if (s[i] && (s[i] == DQUOTE || s[i] == SQUOTE))
		{
			c = s[i++];
			while (s[i] && s[i] != c)
				t[j++] = s[i++];
			if (s[i] && s[i] == c)
				i++;
		}
	}
	t[j] = '\0';
	return (t);
}

char	*rm_quotes(char *s, int n)
{
	char	*res;

	res = malloc(sizeof(char) * ft_strlen(s) - n + 1);
	if (!res)
		return (NULL);
	res = cp_woquotes(s, res);
	free(s);
	return (res);
}

int	ct_quotes(char *p)
{
	int		i;
	int		res;
	char	c;

	i = 0;
	res = 0;
	while (p[i])
	{
		while (p[i] && p[i] != SQUOTE && p[i] != DQUOTE)
			i++;
		if (p[i] && (p[i] == DQUOTE || p[i] == SQUOTE))
		{
			c = p[i];
			res += 2;
			i++;
			while (p[i] && p[i] != c)
				i++;
			if (p[i] && p[i] == c)
				i++;
		}
	}
	return (res);
}

/* Deletes all qutations marks by pairs in all char * included in the
 * char **cmd->args variable.
 */
void	del_quotes(char **s, int n)
{
	int	i;
	int	ct;

	i = 0;
	ct = 0;
	while (s[i])
	{
		if (ft_strchr(s[i], SQUOTE) || ft_strchr(s[i], DQUOTE))
		{
			if ((n == 0 && i > 0 && (s[i - 1][ft_strlen(s[i - 1]) - 1] == '<'
			|| s[i - 1][ft_strlen(s[i - 1]) - 1] == '>')) || n == 1)
			{
				ct = ct_quotes(s[i]);
			 	s[i] = rm_quotes(s[i], ct);
		    }
		}
		i++;
	}
}
