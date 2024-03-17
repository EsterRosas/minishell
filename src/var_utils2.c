/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 20:09:48 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/17 19:14:05 by damendez         ###   ########.fr       */
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

void	assign_str(char *s, char **res, int *i, int *j)
{
	if (s[(*i) + 1] == '?')
		res[*j] = ft_strdup("?");
	else
		res[*j] = var_name(s, (*i) + 1);
	*i = *i + ft_strlen(res[*j]) + 1;
	(*j)++;
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
			assign_str(s, res, &i, &j);
		else
			i++;
	}
	res[j] = NULL;
	return (res);
}
