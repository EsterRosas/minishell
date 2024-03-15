/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:38:16 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/14 20:45:04 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*char	*var_name(char *p, int aft_dl)
{
	int		i;
	char	*res;

	i = aft_dl;
	while (p[i] && ((ft_isalnum(p[i]) || p[i] == '_')))
		i++;
	res = ft_substr(p, aft_dl, i - aft_dl);
	return (res);
}

char	*feed_res(char *s, size_t vname_l, char	*vval, char *res)
{
	int	i;
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (s[j] != '$')
		j++;
	i = j + 1 + vname_l;
	while (vval[k])
	{
		res[j] = vval[k];
		j++;
		k++;
	}
	while (s[i])
	{
		res[j] = s[i];
		i++;
		j++;
	}
	res[j] = '\0';
	return (res);
}

char	*rpl_dlr(char *s, t_envv *o_envp)
{
	char	*res;
	char	*vname;
	char	*vval;
	int		i;
	int		j;
	int		aux;
//		printf("WHILE rpl_dlr s[%i]: %c\n", i, s[i]);

//	printf("rpl_dlr START  s: %s\n", s);
	i = 0;
	j = 0;
	aux = 0;
	while (s[i] != '$' && s[i] != SQUOTE)
		i++;
	if (s[i] == SQUOTE)
	{
		i++;
		while (s[i] != SQUOTE)
			i++;
		i++;
	}
	printf("rpl_dlr 000 s: %s, s[%i]: %c\n", s, i, s[i]);
	if (!s[i])
		return (s);
//	if (s[i]) 
	vname = var_name(s, i + 1);
//	printf("vname %s\n", vname);
	vval = get_oenv(vname, o_envp);
//	printf("vval %s\n", vval);
	res = malloc(ft_strlen(s) - ft_strlen(vname) + ft_strlen(vval));
	if (!res)
		return (NULL);
	printf("i: %i\n", i);
	aux = i;
	i = 0;
	while (i < aux)
	{
		res[j] = s[i];
		i++;
		j++;
	}
//	res[j] = '\0';
	res = feed_res(s, ft_strlen(vname), vval, res);
	free (vname);
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
		{
			val[j] = malloc (sizeof(char) * (ft_strlen(dlr[i]) + 1));
			if (!val[j])
				return (NULL);
			ft_strlcpy(val[j], dlr[i], ft_strlen(dlr[i]) + 1);
	//		printf("IF val[%i]: %s\n", j, val[j]);
		}
		else
		{
			val[j] = rpl_dlr(dlr[i], o_envp);
	//		printf("ELSE val[%i]: %s\n", j, val[j]);
		}
		j++;
		i++;
	}
	val[j] = NULL;
	return (val);
}*/

/* Converts the expanded ** into a new one replacing all$VAR_NAME instances with
 * the corresponding value but only if they are not between single quotes.
 * NOTE: if between double quotes the DO need to get converted.
 */
/*char	**repl_var(char **s, t_envv *o_envp)
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
	//	printf("variables.c repl_var - res[1]: %s\n", res[1]);
		if (need_var(res))
			res = repl_var(res, o_envp);
		free_all(s, dbl_len(s));
		return (res);
	}
}*/
