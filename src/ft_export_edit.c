/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_edit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 12:32:52 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/19 17:02:09 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	create_only(char *nm, t_envv *env)
{
	int	i;

	i = 0;
	while (nm[++i] && nm[i] != '=')
	{
		if (!ft_isalnum(nm[i]) && nm[i] != '_')
		{
			ft_exporterror("export", nm, "not a valid identifier");
			return (-1);
		}
	}
	add_node(nm, env);
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
		if (!ft_isalpha(args[i][0]) && args[i][0] != '_')
			ft_exporterror("export", args[i], "not a valid identifier");
		else
			create_only(args[i], env);
	}
	return (0);
}
