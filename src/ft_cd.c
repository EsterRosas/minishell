/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 20:09:35 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/22 20:58:41 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	upd_pwds(t_envv *env, char *current)
{
	t_envv	*aux;
	char	*s;

	s = malloc(sizeof(char) * (MAXPATHLEN + 1));
	if (!s)
		return ;
	aux = env;
	while (ft_strcmp(aux->nm, "PWD") != 0)
		aux = aux->next;
	if (ft_strcmp(aux->nm, "PWD") == 0)
	{
		free(aux->val);
		aux->val = ft_strdup(getcwd(s, MAXPATHLEN));
	}
	aux = env;
	while (ft_strcmp(aux->nm, "OLDPWD") != 0)
		aux = aux->next;
	if (ft_strcmp(aux->nm, "OLDPWD") == 0)
	{
		if (aux->val)
			free(aux->val);
		aux->val = ft_strdup(current);
	}
	free(s);
//	free(current);
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
		printf("minishell: cd: %s\n", strerror(errno));
		return (-1);
	}
	else
		upd_pwds(env, current);
//	free(current);
	return (0);
}

int	ft_cd(t_cmd *cmd, t_envv *env)
{
	char	*current;
	char	*s;

	s = malloc(sizeof(char) * (MAXPATHLEN + 1));
	if (!s)
		return (-1);
	current = ft_strdup(getcwd(s, MAXPATHLEN));
	free(s);
	if (ft_strcmp(cmd->args[0], "cd") != 0)
		return (0);
	else if (dbl_len(cmd->args) == 1)
	{
		if (cd_only(env, current) == -1)
			return (-1);
	}
	else
	{
		if (chdir(cmd->args[1]) == -1)
			return (-1);
		else
			upd_pwds(env, current);
	}
	free(current);
	return (0);
}
