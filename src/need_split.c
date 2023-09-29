/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   need_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 13:10:36 by erosas-c          #+#    #+#             */
/*   Updated: 2023/09/26 12:23:15 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/defines.h"
#include "../lib/libft/libft.h"	

int	next_quote(char *p, int i, char c)
{
	i++;
	while (p[i] && p[i] != c)
		i++;
	if (p[i] == c)
		i++;
	return (i);
}

int	only_sep(char *s)
{
	if (ft_strlen(s) > 2 && (ft_strchr(s, '<') || ft_strchr(s, '>')))
		return (0);
	else if (ft_strlen(s) > 1 && ft_strchr(s, '|'))
		return (0);
	else if (ft_strlen(s) == 2 && ft_strchr(s, '<') && s[0] != s[1])
		return (0);
	else if (ft_strlen(s) == 2 && ft_strchr(s, '>') && s[0] != s[1])
		return (0);
	return (1);
}

int	some_sep_outq(char *p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		if ((p[i] == '<' || p[i] == '>' || p[i] == '|'))
			return (1);
		else if (p[i] == SQUOTE)
			i = next_quote(p, i, SQUOTE);
		else if (p[i] == DQUOTE)
			i = next_quote(p, i, DQUOTE);
		else
			i++;
	}
	return (0);
}

int	splitable(char *s)
{
	if (!ft_strchr(s, '<') && !ft_strchr(s, '>')
		&& !ft_strchr(s, '|'))
		return (0);
	else if (only_sep(s))
		return (0);
	else if (!ft_strchr(s, SQUOTE) && !ft_strchr(s, DQUOTE))
		return (1);
	else if (some_sep_outq(s))
		return (1);
	else
		return (0);
}

/*checks if the ** rec'd needs to be splitted by checking:
 * 1. If some of the strings included has some separator: <, > OR |
 * 2. If seps are alone in all strings in the **, so would need no split, as they are already splitted
 * 3. If separators are present and not alone we get to the las IF, where we check if the separators are between or outside quotes
 * (only in the 2nd case would need split)
 */
int	need_split(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (splitable(s[i]))
			return (1);
		else
			i++;
	}
	return (0);
}
