/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:32:36 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/14 21:11:35 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*var_name(char *p, int aft_dl)
{
	int		i;
	char	*res;

	i = aft_dl;
	while (p[i] && ((ft_isalnum(p[i]) || p[i] == '_')))
		i++;
	res = ft_substr(p, aft_dl, i - aft_dl);
	return (res);
}

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

char	*rpl_dlr(char *s, t_envv *o_envp)
{
	int		n;
	char	**nms;
	int	i = 0;

	(void)o_envp;
	n = count_vars(s);
	printf("n: %i\n", n);
	nms = get_nms_arr(s, n);
	while (nms[i])
	{
		printf("nms[%i]: %s\n", i, nms[i]);	
		i++;
	}
/*	if (!res)
		return (NULL);
	res->i = 0;
	res->s = NULL;
	while (s[i])
	{
		while (s[i] && s[i] != SQUOTE && s[i] != '$')
			i++;
		if (!s[i])
			break ;
		else if (s[i] && s[i] == SQUOTE)
		{
			i++;
			while (s[i] && s[i] != SQUOTE)
				i++;
			i++; // check
		}
		else  // variable name to be replaced found i = dollar position
			res->s = feed_res(s, res, i, o_envp);
	}*/
	return (nms[0]);
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
			val[j] = malloc (sizeof(char) * (ft_strlen(dlr[i]) + 1));
			if (!val[j])
				return (NULL);
			ft_strlcpy(val[j], dlr[i], ft_strlen(dlr[i]) + 1);
		}
		else
			val[j] = rpl_dlr(dlr[i], o_envp);
		j++;
		i++;
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
		res = malloc (sizeof(char *) * (dbl_len(s) + 1));
		if (!res)
			return (NULL);
		res = nametoval(s, res, o_envp);
/*		if (need_var(res))
			res = repl_var(res, o_envp);*/
		free_all(s, dbl_len(s));
		return (res);
	}
}
