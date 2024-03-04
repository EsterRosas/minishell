/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_edit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 12:32:52 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/04 20:54:10 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	empty_val(t_envv *node)
{
	node->val = malloc(sizeof(char));
	if (!node->val)
		return ;
	node->val[0] = '\0';
}

int	add_new_node(char *evar, t_envv *env)
{
	t_envv	*node;
	int		pos;

	pos = 0;
	node = malloc(sizeof(t_envv));
	if (!node)
		return (1);
	if (ft_strchr(evar, '='))
	{
		pos = ft_strchr(evar, '=') - evar;
		if (evar[pos - 1] == '+')
			node->nm = ft_substr(evar, 0, pos - 1);
		else
			node->nm = ft_substr(evar, 0, pos);
		node->val = ft_substr(evar, pos + 1, ft_strlen(evar) - 1);
		if (!node->val)
			empty_val(node);
	}
	else
		only_name(node, evar);
	node->next = NULL;
	add_env_back(env, node);
	return (0);
}

int	is_inenvlst(char *s, t_envv *env)
{
	char	*new_nm;
	t_envv	*aux;
	int		i;

	i = 0;
	aux = env;
	if (!ft_strchr(s, '=')) // editar quan hi hagi +
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
			return (1);
		aux = aux->next;
	}
	free(new_nm);
	return (0);
}

int	edit_node(char *s, t_envv *env)
{
	char	*nm;
	int		pos;
	t_envv	*aux;
//	char	*tmp;

	pos = 0;
	aux = env;
	if (ft_strchr(s, '='))
	{
		pos = ft_strchr(s, '=') - s;
	/*	if (s[pos - 1] == '+')
		{
			nm = ft_substr(s, 0, pos - 1);
			while (aux)
			{
				if (ft_strcmp(aux->nm, nm) == 0)
				{
					tmp = aux->val;
					free(aux->val);
					aux->val = ft_strjoin(tmp, ft_substr(s, pos + 1, ft_strlen(s) - 1));
					free(nm);
					free(tmp);
					break ;
				}
				aux = aux->next;
			}
		}
		else
		{*/
			nm = ft_substr(s, 0, pos);
			printf("EDIT_NODE s: %s, aux: %p, aux->nm: %s, aux->val: %s\n", s, aux, aux->nm, aux->val);
			while (aux)
			{
				if (ft_strcmp(aux->nm, nm) == 0)
				{
					printf("BEFORE nm: %s\n", nm);
					free(aux->val);
					aux->val = ft_substr(s, pos + 1, ft_strlen(s) - 1);
					free(nm);
					nm = NULL;
					printf("AFTER nm: %s\n", nm);
					break ;
				}
				aux = aux->next;
			}
	//	}
	}
	return (0);
}

/* This function adds a new envvar if it doesn't exist yet and assigns it
 * the vaule specified by the user, if any. If the variable already exists,
 * edits its value according to the user input.
 * First, if some arg (variable) name starts with a char not "-" and not
 * alphanum, it printd the corresponding error
 */
int	ft_edit_envlist(char **args, t_envv *env)
{
	int	i;

	i = 0;
	g_exst = 0;
	while (args[++i])
	{
		if (id_notvalid(args[i]) == 1)
			g_exst = 1;
		else if (!is_inenvlst(args[i], env))
		{
			if (add_new_node(args[i], env) == 1)
				g_exst = 1;
		}
		else if (edit_node(args[i], env) == 1)
			g_exst = 1;
	}
	return (g_exst);
}
