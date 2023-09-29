/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:38:16 by erosas-c          #+#    #+#             */
/*   Updated: 2023/09/28 11:44:46 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/defines.h"
#include "../lib/libft/libft.h"	

char	*var_name(char	*p, int aft_dl)
{
	int		i;
	char	*res;

	res = NULL;
	i = aft_dl;
	while (p[i] && ((ft_isalnum(p[i]) || p[i] == '_')))
		i++;
	return (ft_substr(p, aft_dl, i - aft_dl));
}

static char	*init_dlr(char *s)
{
	char	*one;
	char	*two;
	size_t	vname_l;

	one = getenv(var_name(s, 1));
	two = NULL;
	vname_l = ft_strlen(var_name(s, 1));
	if (ft_strlen(s) == vname_l + 1)
	{
		free(s);
		return (one);
	}
	else
	{
		two = malloc(sizeof(char) * ft_strlen(s));
		if (!two)
			return (NULL);
		two = ft_substr(s, vname_l + 1, ft_strlen(s) - vname_l);
		free(s);
		return (ft_strjoin(one, two));
	}
}

static char	*put_val(char *dl, int j, char **val)
{
	int		i;

	i = 0;
	if (dl[0] == '$')
		val[j] = init_dlr(dl);
	else
		val[j] = mid_dlr(dl);
	return (val[j]);
}

static char	**nametoval(char **dlr, char **val)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (dlr[i])
	{
		if (!has_var(dlr[i]))
		{
			val[j] = malloc (sizeof(char) * (ft_strlen(dlr[i]) + 1));
			if (!val[j])
				return (NULL);
			ft_strlcpy(val[j++], dlr[i], ft_strlen(dlr[i]) + 1);
		}
		else
		{
			val[j] = put_val(dlr[i], j, val);
			j++;
		}
		i++;
	}
	val[j] = NULL;
	return (val);
}

char	**repl_var(char **s, int len)
{
	char	**res;
	int		i;

	res = NULL;
	i = 0;
	if (!need_var(s))
		return (s);
	else
	{
		res = malloc (sizeof(char *) * (len + 1));
		if (!res)
			return (NULL);
		res = nametoval(s, res);
		while (res[i])
			i++;
		if (need_var(res))
			res = repl_var(res, i);
		i = 0;
		while (s[i])
			i++;
		free_all(s, i);
		return (res);
	}
}
