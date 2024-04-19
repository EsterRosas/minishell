/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:52:27 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/31 19:43:22 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	aft_dol_varchr(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '$')
		i++;
	if (s[i] && s[i] == '$')
		i++;
	if (s[i] && (s[i] == '_' || ft_isalnum(s[i]) || s[i] == '?'))
		return (1);
	return (0);
}

char	*get_oenv(char *s, t_envv *o_envp)
{
	char	*res;
	t_envv	*aux;

	aux = o_envp;
	while (aux)
	{
		if (ft_strcmp(s, aux->nm) != 0)
			aux = aux->next;
		else
			break ;
	}
	if (aux == NULL || aux->val == NULL)
		res = ft_strdup("");
	else
		res = ft_strdup(aux->val);
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
	if (!ft_strchr(s, '$') || ft_strcmp(s, "$echo") == 0)
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
