/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   need_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:52:27 by erosas-c          #+#    #+#             */
/*   Updated: 2023/09/27 18:57:59 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/defines.h"
#include "../lib/libft/libft.h"

char	*mid_dlr(char *s)
{
	char	*one;
	char	*two;
	size_t	vname_l;
	int		i;

	i = 0;
	one = NULL;
	two = NULL;
	vname_l = 0;
	while (s[i] && s[i] != '$')
		i++;
	one = ft_substr(s, 0, i);
	two = getenv(var_name(s, ft_strlen(one) + 1));
	vname_l = ft_strlen(var_name(s, ft_strlen(one) + 1));
	if (two && ft_strlen(s) != vname_l + ft_strlen(one))
	{
		i = vname_l + ft_strlen(one) + 1;
		two = ft_strjoin(two, ft_substr(s, i, ft_strlen(s)));
		return (ft_strjoin(one, two));
	}
	return (one);
}

int	some_doll_outq(char *p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		if (p[i] == '$')
			return (1);
		else if (p[i] == SQUOTE)
			i = next_quote(p, i, SQUOTE);
		else
			i++;
	}
	return (0);
}

int	has_var(char *s)
{
	if (!ft_strchr(s, '$'))
		return (0);
	else if (!ft_strchr(s, SQUOTE))
		return (1);
	else if (some_doll_outq(s))
		return (1);
	else
		return (0);
}

int	need_var(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (has_var(s[i]))
			return (1);
		else
			i++;
	}
	return (0);
}
