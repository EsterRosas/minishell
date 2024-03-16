/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:26:22 by damendez          #+#    #+#             */
/*   Updated: 2024/03/16 20:25:38 by erosas-c         ###   ########.fr       */
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

void	check_cmd(t_cmd *cmd)
{
	if (cmd->full_path == NULL)
	{
		if (cmd->args[0][0] == '/' && access(cmd->args[0], F_OK) == 0)
		{
			handle_error(cmd->args[0], "is a directory");
			exit (126);
		}
		else if (cmd->args[0][0] == '/')
		{
			handle_error(cmd->args[0], "No such file or directory");
			exit (127);
		}
		else
		{
			if (ft_strcmp(cmd->args[0], "$\?") == 0)
				handle_error(ft_itoa(g_exst), "command not found");
			else
				handle_error(cmd->args[0], "command not found");
			exit (127);
		}
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
