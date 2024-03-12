/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:52:38 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/12 17:56:03 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*last_spl(char *tr, int l)
{
	char	*sp;

	if (tr[l - 1] == '|' || (tr[l - 1] != tr[l - 2]))
		sp = ft_substr(tr, 0, l - 1);
	else
		sp = ft_substr(tr, 0, l - 2);
	return (sp);
}

char	*first_spl(char *tr)
{
	char	*sp;

	if (tr[0] == '|' || (tr[0] != tr[1]))
		sp = ft_substr(tr, 0, 1);
	else
		sp = ft_substr(tr, 0, 2);
	return (sp);
}

int	is_sep(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int	count_new_ptrs(char **s)
{
	int	num;
	int	i;

	num = 0;
	i = 0;
	while (s[i])
	{
		if ((!ft_strchr(s[i], '<') && !ft_strchr(s[i], '>')
				&& !ft_strchr(s[i], '|')) || only_sep(s[i]))
			i++;
		else
		{
			num++;
			i++;
		}
	}
	return (num);
}
