/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:32:36 by erosas-c          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/03/16 23:23:00 by erosas-c         ###   ########.fr       */
=======
/*   Updated: 2024/03/17 13:14:08 by erosas-c         ###   ########.fr       */
>>>>>>> master
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	upd_indexes(int *i, int *j, char *nm, char	*val)
{
	*i = *i + ft_strlen(nm) + 1;
	*j = *j + ft_strlen(val);
}

void	just_copy(char *s, char *res, int *i, int *j)
{
	res[*j] = s[*i];
	(*j)++;
	(*i)++;
	while (s[*i] && s[*i] != SQUOTE && s[*i] != '$')
	{
		res[*j] = s[*i];
		(*j)++;
		(*i)++;
	}
}

void	squote_or_fullcpy(char *s, int *i, char *res, int *j)
{
	if (s[*i] == SQUOTE)
	{
		res[*j] = s[*i];
		(*j)++;
		(*i)++;
		while (s[*i] && s[*i] != SQUOTE)
		{
			res[*j] = s[*i];
			(*j)++;
			(*i)++;
		}
		res[*j] = s[*i];
		(*j)++;
		(*i)++;
	}
	else
		just_copy(s, res, i, j);
}

char	*do_collage(char *res, char *s, char **nms, char **vals)
{
	int		i;
	int		j;
	int		v;
	char	*aux;

	i = 0;
	j = 0;
	v = 0;
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] && (ft_isalnum(s[i + 1])
				|| s[i + 1] == '_' || s[i + 1] == '?'))
		{
			aux = ft_strdup(res);
			free(res);
			res = ft_strjoin(aux, vals[v]);
			free(aux);
			upd_indexes(&i, &j, nms[v], vals[v]);
			v++;
		}
		else
			squote_or_fullcpy(s, &i, res, &j);
	}
	res[j] = '\0';
	return (res);
}
