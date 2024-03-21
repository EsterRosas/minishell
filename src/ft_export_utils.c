/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:36:50 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/21 17:43:47 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	id_notvalid(char *s)
{
	int	i;

	i = 0;
	if (!ft_isalpha(s[0]) && s[0] != '_')
	{
		ft_exporterror("export", s, "not a valid identifier");
		return (1);
	}
	while (s[++i] && s[i] != '=' && s[i] != '+')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
		{
			ft_exporterror("export", s, "not a valid identifier");
			return (1);
		}
	}
	if (s[i] == '+' && (!s[i + 1] || s[i + 1] != '='))
	{
		ft_exporterror("export", s, "not a valid identifier");
		return (1);
	}
	return (0);
}

void	only_name(t_envv *node, char *evar)
{
	node->nm = ft_strdup(evar);
	node->val = NULL;
}

int	is_inenvlst(char *s, t_envv *env)
{
	char	*new_nm;
	t_envv	*aux;
	int		i;

	i = 0;
	aux = env;
	if (!ft_strchr(s, '='))
		new_nm = ft_strdup(s);
	else
	{
		while (s[i] && s[i] != '=' && s[i] != '+')
			++i;
		new_nm = ft_substr(s, 0, i);
	}
	while (aux)
	{
		if (ft_strcmp(new_nm, aux->nm) == 0)
		{
			free(new_nm);
			return (1);
		}
		aux = aux->next;
	}
	free(new_nm);
	return (0);
}

int	add_new_node(char *evar, t_envv *env)
{
	t_envv	*node;
	size_t	pos;

	pos = 0;
	node = ft_calloc(sizeof(t_envv), 1);
	if (!node)
		return (1);
	if (ft_strchr(evar, '='))
	{
		pos = ft_strchr(evar, '=') - evar;
		node->nm = ft_substr(evar, 0, pos);
		if (pos == ft_strlen(evar) - 1)
			node->val = ft_strdup("");
		else
			node->val = ft_substr(evar, pos + 1, ft_strlen(evar) - pos - 1);
	}
	else
		only_name(node, evar);
	node->next = NULL;
	add_env_back(env, node);
	return (0);
}
