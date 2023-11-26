/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:38:16 by erosas-c          #+#    #+#             */
/*   Updated: 2023/11/26 20:09:21 by erosas-c         ###   ########.fr       */
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

char	*init_dlr(char *s)
{
	char	*one;
	char	*two;
	size_t	vname_l;
	char	*res;

	printf("variable name: %s\n", getenv(var_name(s, 1)));
	one = malloc(sizeof(char) * ft_strlen(getenv(var_name(s, 1))) + 1);
	if (!one)
		return (NULL);
	one = getenv(var_name(s, 1));
	printf("one is: %s\n", one);
	two = NULL;
	vname_l = ft_strlen(var_name(s, 1));
	if (ft_strlen(s) == vname_l + 1)
		res = one;
	else
	{
		/*two = malloc(sizeof(char) * ft_strlen(s));
		if (!two)
			return (NULL);*/
		two = ft_substr(s, vname_l + 1, ft_strlen(s) - vname_l);
		res = ft_strjoin(one, two);
		free(one);
		free(two);
	}
	return (res);

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
		res = nametoval(s, res);
		if (need_var(res))
			res = repl_var(res, o_envp);
		free_all(s, dbl_len(s));
		return (res);
	}
}
