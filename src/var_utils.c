/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   need_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:52:27 by erosas-c          #+#    #+#             */
/*   Updated: 2023/12/02 17:06:31 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/defines.h"
#include "../lib/libft/libft.h"

char	*get_oenv(char *s, t_envv *o_envp)
{
//	int		i;
	char	*res;
	size_t	n;
	char	c;
	t_envv	*aux;

	aux = o_envp;
	n = ft_strlen(s);
//	i = 0;
	c = '\0';
	while (aux)
	{
		if (n > ft_strlen(aux->nm))
			n = ft_strlen(aux->nm);
		if (ft_strlen(aux->nm) != ft_strlen(s)
			|| ft_strncmp(s, aux->nm, n) != 0)
			aux = aux->next;
		else
			break ;
		n = ft_strlen(s);
	}
	if (aux == NULL)
		res = &c;
	else
		res = aux->val;
	free(s);
	return (res);
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
