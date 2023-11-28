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
	//free(p);
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

	i = 0;
	j = 0;
	while (s[i] != '$')
		i++;
	vname = var_name(s, i + 1);
	vval = get_oenv(vname, o_envp);
	res = malloc(sizeof(char) * (ft_strlen(s) - ft_strlen(vname) + ft_strlen(vval)));
	if (!res)
		return (NULL);
	i = 0;
	while (s[i] != '$')
	{
		res[j] = s[i];
		i++;
		j++;
	}
	res = feed_res(s, ft_strlen(vname), vval, res);
	return (res);
}

char	*put_val(char *dl, int j, char **val, t_envv *o_envp)
{
	/*if (dl[0] == '$')*/
		val[j] = rpl_dlr(dl, o_envp);
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
