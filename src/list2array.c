/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 19:52:14 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/12 20:06:45 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	lstsize(t_envv *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

char	*fill_var(t_envv *env_lst)
{
	char	*res;
	size_t	i;
	size_t	j;
	size_t	l;

	l = 0;
	i = -1;
	j = -1;
	if (env_lst->val)
		l = ft_strlen(env_lst->val);
	res = malloc(sizeof(char) * ft_strlen(env_lst->nm) + l + 2);
	if (!res)
		return (NULL);
	while (++i < ft_strlen(env_lst->nm))
		res[i] = env_lst->nm[i];
	if (env_lst->val)
	{
		res[i++] = '=';
		while (++j < ft_strlen(env_lst->val))
			res[i + j] = env_lst->val[j];
	}
	else
		i++;
	res[i + j] = '\0';
	return (res);
}

/* Converts our list with the copy of the environment variables (t_envv)
 * back to a char** so we can have it whenever an execve or another function
 * needs the in the form of a char **
 */
char	**env_lst2arr(t_envv *env_lst)
{
	int		len;
	char	**res;
	int		i;

	i = 0;
	len = lstsize(env_lst);
	res = malloc(sizeof(char *) * len + 1);
	if (!res)
		return (NULL);
	while (i < len)
	{
		res[i] = fill_var(env_lst);
		i++;
		env_lst = env_lst->next;
	}
	res[i] = NULL;
	return (res);
}
