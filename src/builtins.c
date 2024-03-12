/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:56:29 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/12 10:56:32 by erosas-c         ###   ########.fr       */
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
		if (ft_strcmp(env->nm, "PATH") == 0)
			return (0);
		aux = aux->next;
	}
	if (is_echo(s) && ft_strcmp(s, "echo") != 0)
		return (1);
	else //cal afegir casos
		return (0);
}

void	select_builtin(t_prompt *prompt)
{
	if (is_pwd(prompt->cmd->args[0]))
		g_exst = ft_pwd();
	else if (is_echo(prompt->cmd->args[0]))
		g_exst = ft_echo(prompt->cmd);
	else if (is_env(prompt->cmd->args[0]))
		g_exst = ft_env(prompt->envp);
	else if (is_cd(prompt->cmd->args[0]))
		g_exst = ft_cd(prompt->cmd, prompt->envp);
	else if (ft_strcmp(prompt->cmd->args[0], "unset") == 0)
		g_exst = ft_unset(prompt->cmd, prompt->envp);
	else if (ft_strcmp(prompt->cmd->args[0], "export") == 0)
		g_exst = ft_export(prompt->cmd->args, prompt->envp);
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
		if (dbl_len(cmd->args) == 1)  ///revisar aquesta part suposo que com esta ara ft_exit cal passar args i ja esta i adaptar la ft_exit segons aixo
			g_exst = ft_exit(1, cmd->args);
		else
			g_exst = ft_exit(0, cmd->args);
	}
	else
		select_builtin(prompt);
	return (g_exst);
}
