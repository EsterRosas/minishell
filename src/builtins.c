/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:56:29 by erosas-c          #+#    #+#             */
/*   Updated: 2023/12/11 19:13:36 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_builtin(char	*s)
{
	if (ft_strlen(s) == ft_strlen("echo")
		&& ft_strncmp(s, "echo", ft_strlen(s)) == 0)
		return (1);
	else if (ft_strlen(s) == ft_strlen("cd")
		&& ft_strncmp(s, "cd", ft_strlen(s)) == 0)
		return (1);
	else if (ft_strlen(s) == ft_strlen("pwd")
		&& ft_strncmp(s, "pwd", ft_strlen(s)) == 0)
		return (1);
	else if (ft_strlen(s) == ft_strlen("export")
		&& ft_strncmp(s, "export", ft_strlen(s)) == 0)
		return (1);
	else if (ft_strlen(s) == ft_strlen("unset")
		&& ft_strncmp(s, "unset", ft_strlen(s)) == 0)
		return (1);
	else if (ft_strlen(s) == ft_strlen("env")
		&& ft_strncmp(s, "env", ft_strlen(s)) == 0)
		return (1);
	else if (ft_strlen(s) == ft_strlen("exit")
		&& ft_strncmp(s, "exit", ft_strlen(s)) == 0)
		return (1);
	return (0);
}

void	ft_echo(const char *message)
{
	printf("%s\n", message);
}

void	ft_pwd(void)
{
	char	*buf;

	buf = NULL;
	getcwd(NULL, 0);
	printf("%s", buf);
}
