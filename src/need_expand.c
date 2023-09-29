/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   need_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 12:07:30 by erosas-c          #+#    #+#             */
/*   Updated: 2023/09/29 17:32:27 by erosas-c         ###   ########.fr       */
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
char	*mid_virg(char *sp)
{
	int		i;
	char	*one;
	char	*two;

	i = 0;
	one = NULL;
	two = NULL;
	while (sp[i] && sp[i] != '~')
		i++;
	one = malloc(sizeof(char) * i);
	if (!one)
		return (NULL);
	one = ft_substr(sp, 0, i);
	two = malloc(sizeof(char) * (ft_strlen(sp) - i - 1));
	if (!two)
		return (NULL);
	two = ft_substr(sp, i + 1, ft_strlen(sp) - i - 1);
	return (ft_strjoin(ft_strjoin(one, "$HOME"), two));
}

int	some_virg_outq(char *p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		if (p[i] == '~')
			return (1);
		else if (p[i] == SQUOTE)
			i = next_quote(p, i, SQUOTE);
		else if (p[i] == DQUOTE)
			i = next_quote(p, i, DQUOTE);
		else
			i++;
	}
	return (0);
}

/*Checks if any of the strings splitted includes ~ not between quotes*/
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
