/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdtrim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:42:52 by erosas-c          #+#    #+#             */
/*   Updated: 2023/12/07 18:42:54 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	fill_mid_two(char *t, int j, char **spl, size_t len)
{
	size_t	k;
	int		i;

	k = 0;
	i = 0;
	while (t[i] && !is_sep(t[i]))
		i++;
	spl[j++] = ft_substr(t, 0, i);
	k = ft_strlen(spl[j - 1]);
	spl[j++] = ft_substr(t, k, len - k + 1);
	return ;
}

static void	fill_two_spl(char *t, int j, char **spl)
{
	size_t	len;

	len = ft_strlen(t);
	if (is_sep(t[0]))
	{
		spl[j++] = first_spl(t);
		if (ft_strlen(spl[j - 1]) == 1)
			spl[j++] = ft_substr(t, 1, len);
		else
			spl[j++] = ft_substr(t, 2, len - 1);
	}
	else if (is_sep(t[len - 1]))
	{
		spl[j++] = last_spl(t, len);
		if (ft_strlen(spl[j - 1]) == len - 1)
			spl[j++] = ft_substr(t, len - 1, 1);
		else
			spl[j++] = ft_substr(t, len - 2, 2);
	}
	else
		fill_mid_two(t, j, spl, len);
	return ;
}

/* Receives a ** and another newly created to be returned when filled following
 * criteria in cmdsubsplit ft. String by string belonging to trm: checks if it
 * needs to be splitted, 1) if not, copies it to the current position in spl
 * (returned **), 2) otherwise (if yes), checks if the separator by which we
 * have to split the string is: a) at the beginnning, b) at the end OR c) in
 * the middle of the string, and applies the needed fts to fill the next 2 or 3
 * strings depending on the case a, b or c) in split (returned **).*/
static char	**trimtosplit(char **trm, char **spl)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (trm[i])
	{
		if (!splitable(trm[i]))
		{
			spl[j] = malloc (sizeof(char) * (ft_strlen(trm[i]) + 1));
			if (!spl[j])
				return (NULL);
			ft_strlcpy(spl[j++], trm[i], ft_strlen(trm[i]) + 1);
		}
		else
		{
			fill_two_spl(trm[i], j, spl);
			j += 2;
		}
		i++;
	}
	spl[j] = NULL;
	return (spl);
}

/*Creates a new char ** splitting the received one according to the separators
 * it includes, i.e. '>', '<', '|', '>>' and '<<', ONLY if outside quotes, and
 * leaves them alone as a separated char * in the char ** returned.
 * FIRST IF: In case the received char** doesn't need splitting, it returns the
 * same ** rec'd*/
char	**cmdsubsplit(char **s)
{
	char	**res;
	int		len;

	res = NULL;
	len = dbl_len(s);
	if (!need_split(s))
		return (s);
	else
	{
		res = malloc (sizeof(char *) * (count_new_ptrs(s) + len) + 1);
		if (!res)
			return (NULL);
		res = trimtosplit(s, res);
		if (need_split(res))
			res = cmdsubsplit(res);
		free_all(s, dbl_len(s));
		return (res);
	}
}
