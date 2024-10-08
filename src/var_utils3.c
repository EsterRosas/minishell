/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 20:36:18 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/21 17:46:57 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	cp_val(char *res, int j, char *val)
{
	int	i;

	i = 0;
	while (val[i])
	{
		res[j + i] = val[i];
		i++;
	}
}

int	count_sp(char *s, char **nms, char **vals)
{
	int	sp;
	int	nms_sp;
	int	vals_sp;
	int	i;

	i = 0;
	sp = 0;
	nms_sp = 0;
	vals_sp = 0;
	while (nms[i])
	{
		nms_sp = nms_sp + ft_strlen(nms[i]);
		i++;
	}
	i = 0;
	while (vals[i])
	{
		vals_sp = vals_sp + ft_strlen(vals[i]);
		i++;
	}
	sp = ft_strlen(s) + vals_sp - nms_sp - dollars2del(s);
	return (sp);
}

void	sum_ij(int *i, int *j)
{
	(*i)++;
	(*j)++;
}

int	count_vars(char	*s)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (s[i])
	{
		while (s[i] && s[i] != SQUOTE && s[i] != '$')
			i++;
		if (s[i] && s[i] == SQUOTE)
		{
			i++;
			while (s[i] && s[i] != SQUOTE)
				i++;
			i++;
		}
		else if (s[i] && s[i + 1] && (ft_isalnum(s[i + 1]) || s[i + 1] == '_'
				|| s[i + 1] == '?'))
			sum_ij(&i, &res);
		else if (s[i])
			i++;
	}
	return (res);
}

char	**get_vals_arr(char **nms, int ct, t_envv *env)
{
	char	**res;
	int		i;

	i = 0;
	res = ft_calloc(sizeof(char *), ct + 1);
	if (!res)
		return (NULL);
	while (nms[i])
	{
		if (ft_strcmp(nms[i], "?") == 0)
			res[i] = ft_itoa(g_exst);
		else if (is_inenvlst(nms[i], env))
			res[i] = get_oenv(nms[i], env);
		else
			res[i] = ft_strdup("");
		i++;
	}
	res[i] = NULL;
	return (res);
}
