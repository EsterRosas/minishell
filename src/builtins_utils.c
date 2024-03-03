/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:00:20 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/29 18:40:57 by erosas-c         ###   ########.fr       */
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

int	id_notvalid(char *s)
{
	int	i;

	i = 0;
	if (!ft_isalpha(s[0]) && s[0] != '_')
	{
		ft_exporterror("export", s, "not a valid identifier");
		return (1);
	}
	while (s[++i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
		{
			ft_exporterror("export", s, "not a valid identifier");
			return (1);
		}
	}
	return (0);
}

/*int	is_subshell(char *s)
{
	if (s[0] != '.')
		return (0);
	else if (s[1] != '/')
		return (0);
	else if (s[2] != 'm' && s[2] != 'M')
		return (0);
	else if (s[3] != 'i' && s[3] != 'I')
		return (0);
	else if (s[4] != 'n' && s[4] != 'N')
		return (0);
	else if (s[5] != 'i' && s[5] != 'I')
		return (0);
	else if (s[6] != 's' && s[6] != 'S')
		return (0);
	else if (s[7] != 'h' && s[7] != 'H')
		return (0);
	else if (s[8] != 'e' && s[8] != 'E')
		return (0);
	else if (s[9] != 'l' && s[9] != 'L')
		return (0);
	else if (s[10] != 'l' && s[10] != 'L')
		return (0);
	return (1);
}*/
