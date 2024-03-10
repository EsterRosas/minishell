/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 20:09:35 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/10 20:35:48 by erosas-c         ###   ########.fr       */
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
		if (is_inenvlst("PWD", env))
			aux->val = ft_strdup(current);
		else
			aux->val = NULL;
	}
	free(current);
}

void	upd_pwds(t_envv *env)
{
	t_envv	*aux;
	char	*oldpwd_current;

	aux = env;
	if (is_inenvlst("PWD", env))
	{
		while (ft_strcmp(aux->nm, "PWD") != 0)
			aux = aux->next;
		if (ft_strcmp(aux->nm, "PWD") == 0)
		{
			oldpwd_current = ft_strdup(aux->val);
			free(aux->val);
			aux->val = malloc(sizeof(char) * (MAXPATHLEN + 1));
			if (!aux->val)
				return ;
			getcwd(aux->val, MAXPATHLEN);
		}
	}
	if (is_inenvlst("OLDPWD", env))
		upd_oldpwd(env, oldpwd_current);
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
		return (1);
	if (chdir(home) == -1)
	{
		handle_error("cd", home);
		return (1);
	}
	else
		upd_pwds(env);
	return (0);
}

static int	with_args(char *current, t_cmd *cmd, t_envv *env)
{
	char	*old;

	old = get_oenv("OLDPWD", env);
	if (ft_strcmp("-", cmd->args[1]) == 0 && (!old || old[0] == '\0'))
	{
		handle_error("cd", "OLDPWD not set");
		return (1);
	}
	else if (ft_strcmp(cmd->args[1], "-") == 0)
	{
		if (chdir(old) == -1)
		{
			handle_error_opt("cd", old, strerror(errno));
			return (1);
		}
	}
	else if (chdir(cmd->args[1]) == -1)
	{
		handle_error_opt("cd", cmd->args[1], strerror(errno));
		return (1);
	}
	upd_pwds(env);
	free(current);
	return (0);
}

int	ft_cd(t_cmd *cmd, t_envv *env)
{
	char	*current;

	current = malloc(sizeof(char) * (MAXPATHLEN + 1));
	if (!current)
		return (1);
	getcwd(current, MAXPATHLEN);
	if (!cmd->args[1] && ft_strcmp(cmd->args[0], "cd") == 0)
	{
		if (cd_only(env) == 1)
		{
			free(current);
			return (1);
		}
	}
	else if (cmd->args[1] && with_args(current, cmd, env) == 1)
	{
		free(current);
		return (1);
	}
	return (0);
}
