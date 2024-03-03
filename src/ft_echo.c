/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:51:09 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/29 17:47:48 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	is_nopt(char *s)
{
	int	i;

	i = 0;
	if (s[0] != '-')
		return (0);
	else
	{
		while (s[++i])
		{
			if (s[i] != 'n')
				return (0);
		}
	}
	return (1);
}

int	ft_echo(t_cmd *cmd)
{
	int		i;
	int		opt;

	i = 0;
	opt = 0;
	if (dbl_len(cmd->args) == 1 && cmd->infile == 0)
	{
		printf("\n");
		return (0);
	}
	else if (cmd->args[1] && is_nopt(cmd->args[1]))
	{
		opt = 1;
		i++;
	}
	while (cmd->args[++i])
	{
		if (ft_strcmp(cmd->args[i], "$?") == 0)
			cmd->args[i] = ft_itoa(g_exst);
		if (!is_nopt(cmd->args[i]))
		{
			ft_putstr_fd(cmd->args[i], cmd->outfile);
			if (i < dbl_len(cmd->args) - 1)
				ft_putstr_fd(" ", cmd->outfile);
			else if (!opt)
				ft_putstr_fd("\n", cmd->outfile);
		}
	}
	if (cmd->outfile > 2)
		close (cmd->outfile);
//	printf("g_exst: %i\n", g_exst);
	return (0);
}
