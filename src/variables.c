/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:00:19 by erosas-c          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/03/20 15:51:25 by damendez         ###   ########.fr       */
=======
/*   Updated: 2024/03/20 17:30:35 by erosas-c         ###   ########.fr       */
>>>>>>> master
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	dollars2del(char *p)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (p[i])
	{
		if (p[i] == '$')
		{
			n++;
			i++;
		}
		else if (p[i] == SQUOTE)
			i = next_quote(p, i, SQUOTE);
		else
			i++;
	}
	return (n);
}

int	all_vals_empty(char **vals)
{
	int	vals_sp;
	int	i;

	i = 0;
	vals_sp = 0;
	while (vals[i])
	{
		vals_sp = vals_sp + ft_strlen(vals[i]);
		i++;
	}
	if (vals_sp == 0)
		return (1);
	return (0);
}

char	*rpl_dlr(char *s, t_envv *o_envp)
{
	int		n;
	char	**nms;
	char	**vals;
	int		sp;
	char	*res;

	sp = 0;
	n = count_vars(s);
	nms = get_nms_arr(s, n);
	vals = get_vals_arr(nms, n, o_envp);
	if (all_vals_empty(vals))
	{
		res = just_del_names(s, nms, vals);
		free_all(nms, dbl_len(nms));
		return (res);
	}
	sp = count_sp(s, nms, vals);
	res = ft_calloc(sizeof(char), sp + 1);
	if (!res)
		return (NULL);
	res = do_collage(res, s, nms, vals);
	free_all(nms, dbl_len(nms));
	free_all(vals, dbl_len(vals));
	return (res);
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
			val[j] = ft_strdup(dlr[i]);
		else
			val[j] = rpl_dlr(dlr[i], o_envp);
		if (!val[j])
			j--;
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

	if (!need_var(s))
		return (s);
	else
	{
		res = ft_calloc(sizeof(char *), dbl_len(s) + 1);
		if (!res)
			return (NULL);
		res = nametoval(s, res, o_envp);
		free_all(s, dbl_len(s));
		return (res);
	}
}
