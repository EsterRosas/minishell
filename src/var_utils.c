/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   need_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:52:27 by erosas-c          #+#    #+#             */
/*   Updated: 2024/01/17 13:10:16 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	aft_dol_varchr(char *s)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (s[i] && s[i] != '$')
		i++;
	if (s[i] && s[i] == '$')
		i++;
	if (s[i] && (s[i] == '_' || ft_isalnum(s[i])))
		return (1);
	return (0);
}

char	*get_oenv(char *s, t_envv *o_envp)
{
	char	*res;
	size_t	n;
	char	c;
	t_envv	*aux;

	aux = o_envp;
	n = ft_strlen(s);
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
	}
	if (aux == NULL)
		res = &c;
	else
		res = aux->val;
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
	else if (!ft_strchr(s, SQUOTE) && aft_dol_varchr(s))
		return (1);
	else if (some_doll_outq(s) && aft_dol_varchr(s))
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
