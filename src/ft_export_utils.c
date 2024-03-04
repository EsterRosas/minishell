/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:36:50 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/04 20:06:22 by erosas-c         ###   ########.fr       */
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
