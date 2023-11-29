/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_subsplit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 20:25:10 by erosas-c          #+#    #+#             */
/*   Updated: 2023/11/29 19:07:31 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/defines.h"
#include "../lib/libft/libft.h"

void	free_env(t_envv *o_envp)
{
	int	size;

	size = o_envp[0].size;
	while (size > 0)
	{
		free(o_envp[size - 1].nm);
		free(o_envp[size - 1].val);
		size--;
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
