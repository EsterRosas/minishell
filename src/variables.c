/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:38:16 by erosas-c          #+#    #+#             */
/*   Updated: 2023/11/27 20:57:46 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/defines.h"
#include "../lib/libft/libft.h"	

char	*var_name(char *p, int aft_dl)
{
	int		i;
	char	*res;

	i = aft_dl;
	while (p[i] && ((ft_isalnum(p[i]) || p[i] == '_')))
		i++;
	res = ft_substr(p, aft_dl, i - aft_dl);
	free(p);
	return (res);
}

char	*init_dlr(char *s, t_envv *o_envp)
{
	char	*one;
	char	*two;
	char	*three;
	size_t	vname_l;
	int		i = 0;
	(void)o_envp;
//	size_t	vval_l;
//	char	*res;

//	printf("variable name: %s\n", get_oenv(var_name(s, 1)), o_envp);
//	vval_l = ft_strlen(get_oenv(var_name(s, 1), o_envp));
/*	one = malloc(sizeof(char) * vval_l + 1);
	if (!one)
		return (NULL);
	one = get_oenv(var_name(s, 1), o_envp);*/
	while (s[i] != '$')
		i++;
	printf("i: %i\n", i);
	vname_l = ft_strlen(var_name(s, i));
	printf("AFTER i: %i\n", i);
	printf("BEFORE s is: %s\n", s);
	one = ft_substr(s, 0, i);
	printf("s is: %s\n", s);
	printf("one is: %s\n", one);
	printf("len(s): %lu\n", ft_strlen(s));
	two = ft_substr(s, i + 1, ft_strlen(s) - (i + 1));
	printf("i: %i, two is: %s\n", i, two);
	three = ft_substr(two, vname_l, ft_strlen(two));
	two = ft_substr(two, 0, vname_l - 1);
	printf("one: %s\ntwo: %s\nthree: %s\n", one, two, three);
	/*if (ft_strlen(s) == ft_strlen(var_name(s, 1)) + 1)
		res = one;
	else
	{
		two = ft_substr(s, vname_l + 1, ft_strlen(s) - vname_l);
		res = ft_strjoin(one, two);
		free(one);
		free(two);
	}*/
	return (two);
}


char	*put_val(char *dl, int j, char **val, t_envv *o_envp)
{
	/*if (dl[0] == '$')*/
		val[j] = init_dlr(dl, o_envp);
	/*else
		val[j] = mid_dlr(dl, o_envp);*/
	return (val[j]);
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
			ft_strlcpy(val[j++], dlr[i], ft_strlen(dlr[i]) + 1);
		}
		else
		{
			val[j] = put_val(dlr[i], j, val, o_envp);
			j++;
		}
		i++;
	}
	val[j] = NULL;
	return (val);
}

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
		if (need_var(res))
			res = repl_var(res, o_envp);
		free_all(s, dbl_len(s));
		return (res);
	}
}
