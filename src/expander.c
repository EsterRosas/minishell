/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 12:05:20 by erosas-c          #+#    #+#             */
/*   Updated: 2023/11/29 19:05:50 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/defines.h"
#include "../lib/libft/libft.h"	

static char	*init_virg(char *s)
{
	char	*one;
	char	*two;
	char	*res;

	one = malloc(sizeof(char) * 6);
	if (!one)
		return (NULL);
	ft_strlcpy(one, "$HOME", 6);
	two = ft_substr(s, 1, ft_strlen(s) - 1);
	res = ft_strjoin(one, two);
	free(one);
	free(two);
	return (res);
}

static char	*virgtohome(char *spl)
{
	size_t	len;
	char	*res;

	len = ft_strlen(spl);
	if (len == 1)
	{
		res = malloc(sizeof(char) * 6);
		if (!res)
			return (NULL);
		ft_strlcpy(res, "$HOME", 6);
	}
	else
		res = init_virg(spl);
	return (res);
}

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
			exp[j] = malloc (sizeof(char) * (ft_strlen(spl[i]) + 1));
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
		res = malloc (sizeof(char *) * (dbl_len(s) + 1));
		if (!res)
			return (NULL);
		res = spltoexp(s, res);
		if (need_expand(res))
			res = cmdexpand(res);
		free_all(s, dbl_len(s));
		return (res);
	}
}
