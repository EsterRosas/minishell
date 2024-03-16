/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 20:09:48 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/16 12:24:42 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*var_name(char *p, int aft_dl)
{
	int		i;
	char	*res;

	i = aft_dl;
	while (p[i] && ((ft_isalnum(p[i]) || p[i] == '_')))
		i++;
	res = ft_substr(p, aft_dl, i - aft_dl);
	return (res);
}

char	**get_vals_arr(char **nms, int ct, t_envv *env)
{
	char	**res;
	int		i;

	i = 0;
/*	if (!nms[1] && !is_inenvlst(nms[0], env))
		return (NULL);*/
	res = (char **)malloc(sizeof(char *) * ct + 1);
	if (!res)
		return (NULL);
	while (nms[i])
	{
		if (is_inenvlst(nms[i], env))
			res[i] = get_oenv(nms[i], env);
		else
			res[i] = ft_strdup("");
		i++;
	}
	res[i] = NULL;
	return (res);
}

static char	**assign_mem(char **res, int ct)
{
	res = (char **)malloc(sizeof(char *) * ct + 1);
	if (!res)
		return (NULL);
	return (res);
}

static void	upd_i(char *s, int	*i)
{
	(*i)++;
	while (s[*i] && s[*i] != SQUOTE)
		(*i)++;
	(*i)++;
}

char	**get_nms_arr(char *s, int ct)
{
	int		i;
	char	**res;
	int		j;

	j = 0;
	i = 0;
	res = NULL;
	res = assign_mem(res, ct);
	while (s[i])
	{
		while (s[i] && s[i] != SQUOTE && s[i] != '$')
			i++;
		if (!s[i])
			break ;
		else if (s[i] == SQUOTE)
			upd_i(s, &i);
		else if (s[i + 1])
		{
			res[j] = var_name(s, i + 1);
			i = i + ft_strlen(res[j]) + 1;
			j++;
		}
		else
			i++;
	}
	res[j] = NULL;
	return (res);
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
/*		if (!s[i])
			break ;*/
		if (s[i] == SQUOTE)
		{
			i++;
			while (s[i] && s[i] != SQUOTE)
				i++;
			i++;
		}
		else if (s[i + 1] && (ft_isalnum(s[i + 1]) || s[i + 1] == '_')) // variable name to be replaced found i = dollar position
		{
			res++;
			i++;
		}
		else
			i++;
	}
	return (res);
}
