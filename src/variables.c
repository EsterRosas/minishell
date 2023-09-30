/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:38:16 by erosas-c          #+#    #+#             */
/*   Updated: 2023/09/30 19:36:08 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/defines.h"
#include "../lib/libft/libft.h"	

char	*var_name(char	*p, int aft_dl)
{
	int		i;

	i = aft_dl;
	while (p[i] && ((ft_isalnum(p[i]) || p[i] == '_')))
		i++;
	return (ft_substr(p, aft_dl, i - aft_dl));
}

char	*init_dlr(char *s)
{
	char	*one;
	char	*two;
	size_t	vname_l;

	one = malloc(sizeof(char) * ft_strlen(getenv(var_name(s, 1))) + 1);
	if (!one)
		return (NULL);
	one = getenv(var_name(s, 1));
	two = NULL;
	vname_l = ft_strlen(var_name(s, 1));
	if (ft_strlen(s) == vname_l + 1)
		return (one);
	else
	{
		two = malloc(sizeof(char) * ft_strlen(s));
		if (!two)
			return (NULL);
		two = ft_substr(s, vname_l + 1, ft_strlen(s) - vname_l);
		return (ft_strjoin(one, two));
	}
}

char	*put_val(char *dl, int j, char **val)
{
	if (dl[0] == '$')
		val[j] = init_dlr(dl);
	else
		val[j] = mid_dlr(dl);
	return (val[j]);
}

char	**nametoval(char **dlr, char **val)
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
		if (need_var(res))
			res = repl_var(res, i);
		i = 0;
		while (s[i])
			i++;
		//free_all(s, i);
		return (res);
	}
}
