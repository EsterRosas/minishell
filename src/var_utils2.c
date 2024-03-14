/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 20:09:48 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/14 21:18:24 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**get_nms_arr(char *s, int ct)
{
	int		i;
	char	**res;
	int		j;

	j = 0;
	i = 0;
	res = (char **)malloc(sizeof(char *) * ct + 1);
	if (!res)
		return (NULL);
	while (s[i])
	{
		while (s[i] && s[i] != SQUOTE && s[i] != '$')
			i++;
		if (!s[i])
			break ;
		else if (s[i] == SQUOTE)
		{
			i++;
			while (s[i] && s[i] != SQUOTE)
				i++;
			i++;
		}
		else if (s[i + 1]) // variable name to be replaced found i = dollar position
		{
			res[j] = var_name(s, i + 1);
			i = i + ft_strlen(res[j]);
			i++;
			j++;
		}	
	}
	printf("BEFORE  res[0]: %s, res[1]: %s, j: %i\n", res[0], res[1], j);
	res[j] = NULL;
	printf("AFTER res[0]: %s, res[1]: %s\n", res[0], res[1]);
	return (res);
}

int	count_vars(char	*s)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (s[i])
	{
		while (s[i] && s[i] != SQUOTE && s[i] != '$')
			i++;
		if (!s[i])
			break ;
		else if (s[i] == SQUOTE)
		{
			i++;
			while (s[i] && s[i] != SQUOTE)
				i++;
			i++;
		}
		else if (s[i + 1]) // variable name to be replaced found i = dollar position
		{
			res++;
			i++;
		}
	}
	return (res);
}
