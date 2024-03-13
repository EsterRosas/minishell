/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:56:29 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/13 14:36:26 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_env(t_envv *env)
{
	char	**s;
	int		i;

	s = env_lst2arr(env);
	i = -1;
	while (s[++i])
	{
		if (ft_strchr(s[i], '='))
			printf("%s\n", s[i]);
	}
	free_all(s, dbl_len(s));
	return (0);
}

int	ft_pwd(void)
{
	char	*s;
	char	*aux;

	s = malloc(sizeof(char) * (MAXPATHLEN + 1));
	if (!s)
		return (-1);
	aux = ft_strdup(getcwd(s, MAXPATHLEN));
	printf("%s\n", s);
	free(s);
	free(aux);
	return (0);
}

int	path_unset(t_envv *env, char *s)
{
	t_envv	*aux;

	aux = env;
	while (aux)
	{
		if (ft_strcmp(aux->nm, "PATH") == 0)
			return (0);
		aux = aux->next;
	}
	if (is_echo(s) && ft_strcmp(s, "echo") != 0)
		return (1);
	else //cal afegir casos
		return (0);
}

void	select_builtin(t_prompt *prompt, t_cmd *cmd)
{
	if (is_pwd(cmd->args[0]))
		g_exst = ft_pwd();
	else if (is_echo(cmd->args[0]))
		g_exst = ft_echo(cmd);
	else if (is_env(cmd->args[0]))
		g_exst = ft_env(prompt->envp);
	else if (is_cd(cmd->args[0]))
		g_exst = ft_cd(cmd, prompt->envp);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		g_exst = ft_unset(cmd, prompt->envp);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		g_exst = ft_export(cmd->args, prompt->envp);
}

int	ft_exbuiltin(t_prompt *prompt, t_cmd *cmd)
{
	if (path_unset(prompt->envp, cmd->args[0]))
	{
		handle_error(cmd->args[0], "No such file or directory");
		g_exst = 127;
	}
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
	{
		if (dbl_len(cmd->args) == 1)  //potser ja no calen els dos casos
			g_exst = ft_exit(1, cmd);
		else
			g_exst = ft_exit(0, cmd);
	}
	else
		select_builtin(prompt, cmd);
	return (g_exst);
}
