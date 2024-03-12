/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:00:20 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/12 18:13:25 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_echo(char *s)
{
	if (ft_strlen(s) != 4)
		return (0);
	else if (s[0] != 'e' && s[0] != 'E')
		return (0);
	else if (s[1] != 'c' && s[1] != 'C')
		return (0);
	else if (s[2] != 'h' && s[2] != 'H')
		return (0);
	else if (s[3] != 'o' && s[3] != 'O')
		return (0);
	return (1);
}

int	is_pwd(char *s)
{
	if (ft_strlen(s) != 3)
		return (0);
	else if (s[0] != 'p' && s[0] != 'P')
		return (0);
	else if (s[1] != 'w' && s[1] != 'W')
		return (0);
	else if (s[2] != 'd' && s[2] != 'D')
		return (0);
	return (1);
}

int	is_env(char *s)
{
	if (ft_strlen(s) != 3)
		return (0);
	else if (s[0] != 'e' && s[0] != 'E')
		return (0);
	else if (s[1] != 'n' && s[1] != 'N')
		return (0);
	else if (s[2] != 'v' && s[2] != 'V')
		return (0);
	return (1);
}

int	is_cd(char *s)
{
	if (ft_strlen(s) != 2)
		return (0);
	else if (s[0] != 'c' && s[0] != 'C')
		return (0);
	else if (s[1] != 'd' && s[1] != 'D')
		return (0);
	return (1);
}

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
	return (0);
}
