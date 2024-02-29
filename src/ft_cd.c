/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 20:09:35 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/29 19:24:27 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void upd_oldpwd(t_envv *env, char *current)
{
	t_envv *aux;

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
}

static void	upd_pwds(t_envv *env, char *current)
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
			aux->val = malloc(sizeof(char) * (MAXPATHLEN + 1));
			if (!aux->val)
				return ;
			getcwd(aux->val, MAXPATHLEN);
		}
	}
	if (is_inenvlst("OLDPWD", env))
		upd_oldpwd(env, current);
}

static int	cd_only(t_envv *env, char *current)
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
		printf("minishell: cd: %s: %s\n", home, strerror(errno));
		return (-1);
	}
	else
		upd_pwds(env, current);
	return (0);
}

int	with_args(char *current, t_cmd *cmd, t_envv *env)
{
	if (chdir(cmd->args[1]) == -1)
	{
		printf("minishell: cd: %s: %s\n", cmd->args[1], strerror(errno));
		return (1);
	}
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		upd_pwds(env, current);
	else
		chdir(current);
	return (0);
}

int	ft_cd(t_cmd *cmd, t_envv *env)
{
	char	*current;

	current = malloc(sizeof(char) * (MAXPATHLEN + 1));
	if (!current)
		return (-1);
	getcwd(current, MAXPATHLEN);
	if (!cmd->args[1] && ft_strcmp(cmd->args[0], "cd") == 0)
	{
		if (cd_only(env, current) == -1)
		{
			free(current);
			return (1);
		}
	}
	else if (cmd->args[1])
	{
		if (with_args(current, cmd, env) == -1)
			return (1);
	}
	free(current);
	return (0);
}
