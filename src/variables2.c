/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:32:36 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/16 12:56:49 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


/*char	*feed_res(char *s, t_repl *res, int i, t_envv *env) // NEED TO CHANGE HEADER!!
{
	char	*vname;
	char	vval;
	int		j;

	vname = var_name(s, i + 1);
	val = get_oenv(vname, env);
	res->s = malloc(sizeof(char) * (ft_strlen(s) - ft_strlen(vname) + ft_strlen(vval)));
	if (!res->s)
		return (NULL);
	while (res->i < i)
	{
		res->s[res->i] = s[i];
		i++;
	}
	while (s[i])
	{
		res[j] = s[i];
		i++;
		j++;
	}
	res[j] = '\0';
	return (res);
}*/

int	count_sp(char *s, char **nms, char **vals)
{
	int	sp;
	int	nms_sp;
	int	vals_sp;
	int i;

	i = 0;
	sp = 0;
	nms_sp = 0;
	vals_sp = 0;
	while (nms[i])
	{
		nms_sp = nms_sp + ft_strlen(nms[i]);
		i++;
	}
	while (vals[i])
	{
		vals_sp = vals_sp + ft_strlen(vals[i]);
		i++;
	}
//	printf("count sp\n");
	sp = ft_strlen(s) - nms_sp + vals_sp;
	return (sp);
}

void	paste_quoted(char *s, int *i, char *res, int *j)
{
//	printf("enters paste quoted, s[%i]: %c, j: %i\n", *i, s[*i], *j);
	res[*j] = s[*i];
	(*j)++;
	(*i)++;
//	printf("enters paste quoted, i: %i, j: %i\n", *i, *j);
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

char	*do_collage(char *res, char *s, char **nms, char **vals)
{
	int		i;
	int		j;
	int 	v;
	char	*aux;

	i = 0;
	j = 0;
	v = 0;
//	printf("do collage s[%i]: %c\n", i, s[i]);

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
		else if (s[i] == SQUOTE)
			paste_quoted(s, &i, res, &j);
		else
			just_copy(s, res, &i, &j);
	}
	res[j] = '\0';
	return (res);
}

char	*rpl_dlr(char *s, t_envv *o_envp)
{
	int		n;
	char	**nms;
	char	**vals;
	int		sp;
	char	*res;
//	printf("variables2.c rpl_dlr s: %s\n", s);

	sp = 0;
	n = count_vars(s);
	nms = get_nms_arr(s, n);
	vals = get_vals_arr(nms, n, o_envp);
/*	if (!vals)
	{
		free_all(nms, dbl_len(nms));
		return (NULL);
	}*/
	sp = count_sp(s, nms, vals); 
//	printf("sp: %i\n", sp);
	res = (char *)malloc(sizeof(char) * sp + 1);
	if (!res)
		return (NULL);
	res = do_collage(res, s, nms, vals);
	free_all(nms, dbl_len(nms));
	free_all(vals, dbl_len(vals));
	return (res);
}

static void sum_ij(int *i, int *j)
{
	(*i)++;
	(*j)++;
}

char	**nametoval(char **dlr, char **val, t_envv *o_envp)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (dlr[i])
	{
		if (!has_var(dlr[i]))
		{
			val[j] = malloc(sizeof(char) * (ft_strlen(dlr[i]) + 1));
			if (!val[j])
				return (NULL);
			ft_strlcpy(val[j], dlr[i], ft_strlen(dlr[i]) + 1);
		}
		else
			val[j] = rpl_dlr(dlr[i], o_envp);
		sum_ij(&i, &j);
	}
	if (!val[0])
	{
		free_all(val, dbl_len(val));
		return (NULL);
	}
	val[j] = NULL;
	return (val);
}

/* Converts the expanded ** into a new one replacing all$VAR_NAME instances with
 * the corresponding value but only if they are not between single quotes.
 * NOTE: if between double quotes the DO need to get converted.
 */
char	**repl_var(char **s, t_envv *o_envp)
{
	char	**res;
//	printf("variables2 repl var need_var(s): %i, s[1]: %s\n", need_var(s), s[1]);

	if (!need_var(s))
		return (s);
	else
	{
		res = (char **)malloc(sizeof(char *) * (dbl_len(s) + 1));
		if (!res)
			return (NULL);
		res = nametoval(s, res, o_envp);
		free_all(s, dbl_len(s));
		return (res);
	}
}
