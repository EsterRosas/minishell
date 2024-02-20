/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 20:09:35 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/20 20:55:21 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	upd_pwd(t_envv *env, char *home)
{
	t_envv	*aux;

	aux = env;
	while (ft_strcmp(aux->nm, "PWD") != 0)
		aux = aux->next;
	if (ft_strcmp(aux->nm, "PWD") == 0)
	{
		free(aux->val);
		aux->val = ft_strdup(home);
	}
}

static int	cd_only(t_envv *env)
{
	t_envv	*aux;
	char	*home;

	aux = env;
	while (aux && ft_strcmp(aux->nm, "HOME") != 0)
		aux = aux->next;
	if (ft_strcmp(aux->nm, "HOME") == 0)
		home = aux->val;
	else
		return (-1);
	if (chdir(home) == -1)
	{
		printf("minishell: cd: %s\n", strerror(errno));
		return (-1);
	}
	else
		upd_pwd(env, home);
	return (0);
}

int	ft_cd(t_cmd *cmd, t_envv *env)
{
	if (ft_strcmp(cmd->args[0], "cs") != 0)
		return (0); // segur?
	else if (dbl_len(cmd->args) == 1)
	{
		if (cd_only(env) == -1)
			return (-1);
	}
	else
	{
		if (chdir(cmd->args[1]) == -1)
		{
			printf("chdir returns -1\n");
			return (-1);
		}
		else
		{
			printf("000 ELSE ft_cd, so ch_dir is OK\n");
			upd_pwd(env, cmd->args[1]);
		}
	}
	return (0);
}
