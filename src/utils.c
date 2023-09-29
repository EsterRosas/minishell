/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:52:38 by erosas-c          #+#    #+#             */
/*   Updated: 2023/09/23 12:50:06 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/defines.h"
#include "../lib/libft/libft.h"

char	*mid_spl(char *tr)
{
	char	*sp;
	int		i;

	i = 0;
	while (tr[i] && !is_sep(tr[i]))
		i++;
	sp = malloc (sizeof(char) * i + 1);
	if (!sp)
		return (NULL);
	sp = ft_substr(tr, 0, i);
	return (sp);
}

char	*last_spl(char *tr, int l)
{
	char	*sp;

	if (tr[l - 1] == '|' || (tr[l - 1] != tr[l - 2]))
	{
		sp = malloc (sizeof(char) * l - 1);
		if (!sp)
			return (NULL);
		sp = ft_substr(tr, 0, l - 1);
	}
	else
	{
		sp = malloc (sizeof(char) * l - 2);
		if (!sp)
			return (NULL);
		sp = ft_substr(tr, 0, l - 2);
	}
	return (sp);
}

char	*first_spl(char *tr)
{
	char	*sp;

	if (tr[0] == '|' || (tr[0] != tr[1]))
	{
		sp = malloc (sizeof(char) + 1);
		if (!sp)
			return (NULL);
		sp = ft_substr(tr, 0, 1);
	}
	else
	{
		sp = malloc (sizeof(char) * 2 + 1);
		if (!sp)
			return (NULL);
		sp = ft_substr(tr, 0, 2);
	}
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
