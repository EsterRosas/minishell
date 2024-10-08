/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 12:05:20 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/19 18:37:35 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	**spltoexp(char **spl, char **exp)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (spl[i])
	{
		if (!expandable(spl[i]))
		{
			exp[j] = ft_calloc (sizeof(char), ft_strlen(spl[i]) + 1);
			if (!exp[j])
				return (NULL);
			ft_strlcpy(exp[j++], spl[i], ft_strlen(spl[i]) + 1);
		}
		else
		{
			exp[j] = virgtohome(spl[i]);
			j++;
		}
		i++;
	}
	exp[j] = NULL;
	return (exp);
}

int	need_expand(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i][0] == '~' && (ft_strlen(s[i]) <= 1))
			return (1);
		else if (s[i][0] == '~' && s[i][1] == '/')
			return (1);
		else
			i++;
	}
	return (0);
}

/* Converts the splitted ** into a new one replacing all ~ instances with $HOME
 * but only if they are not between quotes. NOTE: BASH only converts ~ to $HOME
 * when it's alone in the "string" or has "/" after it to include subfolders
 */
char	**cmdexpand(char **s)
{
	char	**res;

	if (!need_expand(s))
		return (s);
	else
	{
		res = ft_calloc(sizeof(char *), dbl_len(s) + 1);
		if (!res)
			return (NULL);
		res = spltoexp(s, res);
		if (need_expand(res))
			res = cmdexpand(res);
		free_all(s, dbl_len(s));
		return (res);
	}
}
