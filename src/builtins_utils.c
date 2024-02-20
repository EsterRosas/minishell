/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:00:20 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/20 21:01:17 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
