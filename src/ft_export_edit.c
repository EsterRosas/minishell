/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_edit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 12:32:52 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/17 13:55:51 by erosas-c         ###   ########.fr       */
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
			ft_printerror("export", nm, "not a valid identifier");
			return (-1);
		}
	}
	add_node(nm, env);
	return (0);
}

int	ft_edit_envlist(char **args, t_envv *env)
{
	int	i;

	i = 0;
	while (args[++i])
	{
		if (!ft_isalpha(args[i][0]) && args[i][0] != '_')
			ft_printerror("export", args[i], "not a valid identifier");
		else
			create_only(args[i], env);
	}
	return (0);
}
