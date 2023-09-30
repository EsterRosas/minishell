/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 12:05:20 by erosas-c          #+#    #+#             */
/*   Updated: 2023/09/30 10:39:17 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/defines.h"
#include "../lib/libft/libft.h"	

static char	*init_virg(char *s)
{
	char	*one;
	char	*two;

	one = NULL;
	two = NULL;
	if (ft_strlen(s) == 1)
		return (s);
	else
	{
		one = malloc(sizeof(char) * 6);
		if (!one)
			return (NULL);
		one = "$HOME";
		two = malloc(sizeof(char) * ft_strlen(s));
		if (!two)
			return (NULL);
		two = ft_substr(s, 1, ft_strlen(s) - 1);
		return (ft_strjoin(one, two));
	}
}

static char	*virgtohome(char *spl)
{
	size_t	len;
	char	*res;

	res = NULL;
	len = ft_strlen(spl);
	if (len == 1)
	{
		res = malloc(sizeof(char) * 6);
		if (!res)
			return (NULL);
		res = "$HOME";
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
 * but only if they are not between quotes. Seen that BASH only converts ~ to
 * $HOME when it's alone in the "string"
 */
char	**cmdexpand(char **s, int len)
{
	char	**res;
	int		i;

	res = NULL;
	i = 0;
	if (!need_expand(s))
		return (s);
	else
	{
		res = malloc (sizeof(char *) * (len + 1));
		if (!res)
			return (NULL);
		res = spltoexp(s, res);
		while (res[i])
			i++;
		if (need_expand(res))
			res = cmdexpand(res, i);
		i = 0;
		while (s[i])
			i++;
		free_all(s, i);
		return (res);
	}
}
