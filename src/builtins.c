/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:56:29 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/04 17:33:16 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_builtin(char	*s)
{
	if (is_echo(s))
		return (1);
	else if (is_cd(s))
		return (1);
	else if (is_pwd(s))
		return (1);
	else if (ft_strlen(s) == ft_strlen("export")
		&& ft_strncmp(s, "export", ft_strlen(s)) == 0)
		return (1);
	else if (ft_strlen(s) == ft_strlen("unset")
		&& ft_strncmp(s, "unset", ft_strlen(s)) == 0)
		return (1);
	else if (is_env(s))
		return (1);
	else if (ft_strlen(s) == ft_strlen("exit")
		&& ft_strncmp(s, "exit", ft_strlen(s)) == 0)
		return (1);
//	else if (ft_strlen(s) == 11 && is_subshell(s))
//		return (1);
	return (0);
}

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

void	ft_exit(int print)
{
	if (print == 1)
		printf("exit\n");
	g_exst = 0;
//	printf("g_exst: %i\n", g_exst);
	restore_terminal_settings();
	exit (g_exst);
}

int	ft_exbuiltin(t_prompt *prompt, t_cmd *cmd)
{
	if (ft_strcmp(cmd->args[0], "exit") == 0)
	{
		if (dbl_len(cmd->args) == 1)
			ft_exit(1);
		else
			ft_exit(0);
	}
	else if (is_pwd(cmd->args[0]))
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
//	else if (is_subshell(cmd->args[0]))
//		g_exst = upd_shlvl(prompt->envp);
	return (g_exst);
}
