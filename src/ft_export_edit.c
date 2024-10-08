/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_edit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 12:32:52 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/21 17:41:42 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	replace_value(char *s, t_envv *aux, int pos)
{
	char	*nm;
	int		len;

	len = ft_strlen(s);
	nm = ft_substr(s, 0, pos);
	while (aux)
	{
		if (ft_strcmp(aux->nm, nm) == 0)
		{
			free(aux->val);
			aux->val = ft_substr(s, pos + 1, len - pos - 1);
			break ;
		}
		aux = aux->next;
	}
	free(nm);
}

static void	join_values(char *s, t_envv *aux, int pos)
{
	char	*nm;
	char	*tmp;
	char	*tmp2;

	nm = ft_substr(s, 0, pos - 1);
	while (aux)
	{
		if (ft_strcmp(aux->nm, nm) == 0)
		{
			tmp = ft_strdup(aux->val);
			free(aux->val);
			tmp2 = ft_substr(s, pos + 1, ft_strlen(s) - pos - 1);
			aux->val = ft_strjoin(tmp, tmp2);
			free(tmp);
			free(tmp2);
			break ;
		}
		aux = aux->next;
	}
	free(nm);
}

static int	edit_node(char *s, t_envv *env)
{
	int		pos;
	t_envv	*aux;

	pos = 0;
	aux = env;
	if (ft_strchr(s, '='))
	{
		pos = ft_strchr(s, '=') - s;
		if (s[pos - 1] == '+')
			join_values(s, aux, pos);
		else
			replace_value(s, aux, pos);
	}
	return (0);
}

/* This function adds a new envvar if it doesn't exist yet and assigns it
 * the vaule specified by the user, if any. If the variable already exists,
 * edits its value according to the user input.
 * First, if some arg (variable) name starts with a char not "-" and not
 * alphanum, it printd the corresponding error
 */
int	ft_edit_envlist(char *arg, t_envv *env)
{
	g_exst = 0;
	if (!is_inenvlst(arg, env))
	{
		if (add_new_node(arg, env) == 1)
			g_exst = 1;
	}
	else if (edit_node(arg, env) == 1)
		g_exst = 1;
	return (g_exst);
}
