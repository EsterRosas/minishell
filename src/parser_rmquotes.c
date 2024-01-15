/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_rmquotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:52:06 by erosas-c          #+#    #+#             */
/*   Updated: 2024/01/15 17:45:06 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*char	*rm_quotes(int n, char *s)
{
	char	*res;

	res = ft_substr(s, n, ft_strlen(s) - (n * 2));
	free(s);
	return (res);
}*/

/* Delete quotation marks at the first position and last of all the strings
 * as far as they are in both places and are the same. If more than one, need to
 * be the same type (squotes or dquotes) as the ones in the initial ends,
 * according to bash behaviour.
 */
/*void	del_end_quotes(char **args)
{
	int	i;
	int	l;
	int	j;

	i = 0;
	l = 0;
	j = 0;
	while (args[i])
	{
		l = ft_strlen(args[i]);
		if (l > 1 && args[i][0] == SQUOTE && args[i][l - 1] == SQUOTE)
		{
			while (args[i][j] == SQUOTE && args[i][l - 1 - j] == SQUOTE)
				j++;
			args[i] = rm_quotes(j, args[i]);
		}
		else if (l > 1 && args[i][0] == DQUOTE && args[i][l - 1] == DQUOTE)
		{
			while (args[i][j] == DQUOTE && args[i][l - 1 - j] == DQUOTE)
				j++;
			args[i] = rm_quotes(j, args[i]);
		}
		i++;
	}
}*/

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

char	*rm_midquot(char *s, int n)
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

/* IN PROGRESS. Once done, maybe it can also include the movements needed for
 * del_end_quotes. DONE. I think it works when not applying del_end_quotes,
 * for the moment corresponding functions are commented just in case
 */
void	del_mid_quotes(char **s)
{
	int	i;
	int	ct;

	i = 0;
	ct = 0;
	while (s[i])
	{
		if (ft_strchr(s[i], SQUOTE) || ft_strchr(s[i], DQUOTE))
		{
			ct = ct_quotes(s[i]);
			s[i] = rm_midquot(s[i], ct);
		}
		i++;
	}
}
