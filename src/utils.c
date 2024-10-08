/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_subsplit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 20:25:10 by erosas-c          #+#    #+#             */
/*   Updated: 2023/12/11 17:36:02 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

void	add_env_back(t_envv *env_lst, t_envv *new)
{
	t_envv	*aux;

	aux = env_lst;
	if (env_lst == NULL)
		env_lst = new;
	else
	{
		while (aux->next)
			aux = aux->next;
		aux->next = new;
	}
	new->next = NULL;
}

void	free_env(t_envv *o_envp)
{
	t_envv	*temp;

	temp = o_envp->next;
	while (o_envp)
	{
		temp = o_envp->next;
		free(o_envp->nm);
		free(o_envp->val);
		free(o_envp);
		o_envp = temp;
	}
	free(o_envp);
}

int	expandable(char *s)
{
	if (s[0] == '~' && (ft_strlen(s) <= 1))
		return (1);
	else if (s[0] == '~' && s[1] == '/')
		return (1);
	return (0);
}

int	dbl_len(char **s)
{
	char	**aux;
	int		i;

	aux = s;
	i = 0;
	while (*aux != NULL)
	{
		aux++;
		i++;
	}
	return (i);
}
