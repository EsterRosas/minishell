/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varibles.4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 12:22:51 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/17 13:32:22 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_assign_mem(char *res, int ct)
{
	res = (char *)malloc(sizeof(char) * ct + 1);
	if (!res)
		return (NULL);
	return (res);
}

static int	upd_i(char *s, int i)
{
	i++;
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		i++;
	return (i);
}

char	*just_del_names(char *s, char **nms, char **vals)
{
	char	*res;
	int		sp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	sp = count_sp(s, nms, vals);
	if (sp == 0)
		return (NULL);
	res = (char *)malloc(sizeof(char) * sp + 1);
	if (!res)
		return (NULL);
	while (s[i])
	{
		if (s[i] != SQUOTE && s[i] != '$')
			res[j++] = s[i++];
		else if (s[i] == SQUOTE)
			i = next_quote(s, i, SQUOTE);
		else
			i = upd_i(s, i);
	}
	return (res);
}
