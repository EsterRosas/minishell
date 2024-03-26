/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:26:22 by damendez          #+#    #+#             */
/*   Updated: 2024/03/25 20:43:27 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	check_executable(t_cmd *cmd)
{
	if (access(cmd->full_path, X_OK) == -1)
	{
		handle_error(cmd->args[0], "Permission denied");
		exit(126);
	}
}

static void	cmd_notfound(char *arg)
{
	if (access(arg, F_OK) == 0)
		handle_error(arg, "is a directory");
	else if (ft_strcmp(arg, "$\?") == 0)
		handle_error(ft_itoa(g_exst), "command not found");
	else
		handle_error(arg, "command not found");
	exit (127);
}

void	check_cmd(t_cmd *cmd, t_envv *env)
{
	if (cmd->full_path == NULL)
	{
		if (cmd->args[0][0] == '/' && (access(cmd->args[0], F_OK) == 0
			|| cmd->args[0][ft_strlen(cmd->args[0]) - 1] == '/'))
		{
			if (access(cmd->args[0], F_OK) == 0)
				handle_error(cmd->args[0], "is a directory");
			else
				handle_error(cmd->args[0], "Not a directory");
			exit (126);
		}
		else if (cmd->args[0][0] == '/' || path_unset(env, cmd->args[0]))
		{
			handle_error(cmd->args[0], "No such file or directory");
			exit (127);
		}
		else
			cmd_notfound(cmd->args[0]);
	}
	else
		check_executable(cmd);
}

int	ft_chdir(char *s)
{
	if (chdir(s) == -1)
	{
		handle_error_opt("cd", s, strerror(errno));
		return (-1);
	}
	return (0);
}

int	has_nonum(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && (s[i] < '0' || s[i] > '9'))
		i++;
	if (ft_strlen(s) == 2 && s[0] == '-' && s[1] == '-')
		return (0);
	else if (i == ft_strlen(s))
		return (1);
	return (0);
}
