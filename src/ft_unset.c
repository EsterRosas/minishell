/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 20:10:58 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/27 19:18:30 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	del_node(char *str, t_envv *env)
{
	t_envv	*aux;
	t_envv	*temp;

	aux = env;
	while (aux->next)
	{
		if (ft_strcmp(aux->next->nm, str) == 0)
		{
			temp = aux->next;
			aux->next = aux->next->next;
			free(temp->nm);
			free(temp->val);
			free(temp);
		}
		else
			aux = aux->next;
	}
}

int	do_unset(char *str, t_envv *env)
{
	int		i;
	t_envv	*aux;

	aux = env;
	i = 0;
	while (str[++i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			ft_exporterror("unset", str, "not a valid identifier");
			return (1);
		}
	}
	if (aux->nm == str)
	{
		env = env->next;
		free(aux->nm);
		free(aux->val);
		free(aux);
		return (0);
	}
	else
		del_node(str, env);
	return (0);
}

int	ft_unset(t_cmd *cmd, t_envv *env)
{
	int	i;

	i = 0;
	if (dbl_len(cmd->args) == 1)
		return (0);
	else
	{
		while (cmd->args[++i])
		{
			if (!ft_isalpha(cmd->args[i][0]) && cmd->args[i][0] != '_')
			{
				ft_exporterror("unset", cmd->args[i], "not a valid identifier");
				return (1);
			}
			else if (do_unset(cmd->args[i], env) == 1)
				return (1);
		}
	}
	return (0);
}
