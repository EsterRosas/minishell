/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:36:50 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/17 14:34:44 by erosas-c         ###   ########.fr       */
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

void	assign_empty_val(char *val)
{
	printf("assign empty val\n");
/*	val = malloc(sizeof(char));
	if (!val)
		return ;*/
	val = ft_strdup("");;
	printf("assign empty val, val: %s\n", val);
}

int	add_new_node(char *evar, t_envv *env)
{
	t_envv	*node;
	size_t	pos;

	printf("enters add new node export utils, evar: %s\n", evar);
	pos = 0;
	node = malloc(sizeof(t_envv));
	if (!node)
		return (1);
	if (ft_strchr(evar, '='))
	{
		pos = ft_strchr(evar, '=') - evar;
		if (evar[pos - 1] == '+')
		{
			node->nm = ft_substr(evar, 0, pos - 1);
			printf("111 node->nm: %s\n", node->nm);
		}
		else
		{
			node->nm = ft_substr(evar, 0, pos);
			printf("222 node->nm: %s\n", node->nm);
		}
		if (pos == ft_strlen(evar) - 1)
		{
			assign_empty_val(node->val);
			//printf("333 node->nm: %s, node->val: %s\n", node->nm, node->val);
		}
		else
		{
			node->val = ft_substr(evar, pos + 1, ft_strlen(evar) - 1);
			printf("444 node->nm: %s, node->val: %s\n", node->nm, node->val);
		}
	}
	else
		only_name(node, evar);
	node->next = NULL;
	add_env_back(env, node);
	return (0);
}
