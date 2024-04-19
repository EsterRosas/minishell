/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 20:09:35 by erosas-c          #+#    #+#             */
/*   Updated: 2024/04/01 15:47:04 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	upd_oldpwd(t_envv *env, char *current)
{
	t_envv	*aux;

	aux = env;
	while (ft_strcmp(aux->nm, "OLDPWD") != 0)
		aux = aux->next;
	if (ft_strcmp(aux->nm, "OLDPWD") == 0)
	{
		if (aux->val)
			free(aux->val);
		aux->val = ft_strdup(current);
	}
}

void	upd_pwds(t_envv *env, char *oldpwd_current)
{
	t_envv	*aux;

	aux = env;
	if (is_inenvlst("PWD", env))
	{
		while (ft_strcmp(aux->nm, "PWD") != 0)
			aux = aux->next;
		if (ft_strcmp(aux->nm, "PWD") == 0)
		{
			free(aux->val);
			aux->val = upd_auxval();
		}
	}
	if (is_inenvlst("OLDPWD", env))
		upd_oldpwd(env, oldpwd_current);
}

int	cd_only(t_envv *env)
{
	t_envv	*aux;
	char	*home;

	aux = env;
	while (aux && ft_strcmp(aux->nm, "HOME") != 0)
		aux = aux->next;
	if (aux == NULL)
	{
		handle_error("cd", "HOME not set");
		return (1);
	}
	else if (ft_strcmp(aux->nm, "HOME") == 0)
		home = aux->val;
	if (chdir(home) == -1)
	{
		handle_error("cd", home);
		return (1);
	}
	return (0);
}

static int	with_args(t_cmd *cmd, t_envv *env)
{
	(void)env;
	if (cmd->args[1][0] == '\0')
		return (0);
	else if (ft_chdir(cmd->args[1]) == -1)
		return (1);
	return (0);
}

int	ft_cd(t_cmd *cmd, t_envv *env)
{
	char	*oldpwd_current;

	oldpwd_current = ft_calloc(sizeof(char), (MAXPATHLEN + 1));
	if (!oldpwd_current)
		return (1);
	oldpwd_current = getcwd(oldpwd_current, MAXPATHLEN);
	if (!cmd->args[1] && ft_strcmp(cmd->args[0], "cd") == 0)
	{
		if (do_cdonly(env, oldpwd_current) == 1)
			return (1);
	}
	else if (cmd->args[1])
	{
		if (with_args(cmd, env) == 1)
		{
			free(oldpwd_current);
			return (1);
		}
		else
			upd_pwds(env, oldpwd_current);
	}
	free(oldpwd_current);
	return (0);
}
