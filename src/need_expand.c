/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   need_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 12:07:30 by erosas-c          #+#    #+#             */
/*   Updated: 2023/09/29 19:54:23 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/defines.h"
#include "../lib/libft/libft.h"	

int	expandable(char *s)
{
	if (s[0] == '~' && (ft_strlen(s) <= 1))
		return (1);
	else if (s[0] == '~' && s[1] == '/')
		return (1);
	return (0);
}

/* Checks if any of the strings splitted includes ~ at the beginning and in
 * case its length > 1 that the 2nd char is '/'
 */
int	need_expand(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (expandable(s[i]))
			return (1);
		else
			i++;
	}
	return (0);
}
