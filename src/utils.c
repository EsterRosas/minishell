/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_subsplit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 20:25:10 by erosas-c          #+#    #+#             */
/*   Updated: 2023/12/04 20:17:06 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/defines.h"
#include "../lib/libft/libft.h"

void	add_env_back(t_envv *env_lst, t_envv *new)
{
	t_envv	*aux;

	aux = env_lst;
	if (env_lst == NULL)
		env_lst = new;
	else
	{
		while (aux->next)
		{
			aux = aux->next;
		}
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
