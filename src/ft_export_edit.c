/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_edit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 12:32:52 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/22 20:55:19 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
		node->nm = ft_substr(evar, 0, pos);
		node->val = ft_substr(evar, pos + 1, ft_strlen(evar) - 1);
	}
	else
	{
		node->nm = ft_strdup(evar);
		node->val = NULL;
	}
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
	if (!ft_strchr(s, '='))
		new_nm = s;
	else
	{
		while (s[i] && s[i] != '=')
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

int	id_notvalid(char *s)
{
	int	i;

	i = 0;
	if (!ft_isalpha(s[0]) && s[0] != '_')
	{	
		ft_exporterror("export", s, "not a valid identifier");
		return (1);
	}
	while (s[++i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
		{
			ft_exporterror("export", s, "not a valid identifier");
			return (1);
		}
	}
	return (0);
}

int	edit_node(char *s, t_envv *env)
{
	char	*nm;
	int		pos;
	t_envv	*aux;

	pos = 0;
	aux = env;
	if (ft_strchr(s, '='))
	{
		pos = ft_strchr(s, '=') - s;
		nm = ft_substr(s, 0, pos);
		while (aux)
		{
			if (ft_strcmp(aux->nm, nm) == 0)
			{
				free(aux->val);
				aux->val = ft_substr(s, pos + 1, ft_strlen(s) - 1);
				free(nm);
				break ;
			}
			aux = aux->next;
		}	
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
	while (args[++i])
	{
		if (id_notvalid(args[i]) == 1)
			return (1);
		else if (!is_inenvlst(args[i], env))
		{
			if (add_new_node(args[i], env) == 1)
				return (1);
		}
		else if (edit_node(args[i], env) == 1)
			return (1);
	}
	return (0);
}
