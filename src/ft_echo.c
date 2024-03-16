/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:51:09 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/16 15:05:08 by erosas-c         ###   ########.fr       */
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

static void	echo_print(t_cmd *cmd, int opt, int i)
{
	while (cmd->args[i])
	{
		if (!is_nopt(cmd->args[i]) || i > 1)
		{
			ft_putstr_fd(cmd->args[i], cmd->outfile);
			if (i < dbl_len(cmd->args) - 1)
				ft_putstr_fd(" ", cmd->outfile);
			else if (!opt)
				ft_putstr_fd("\n", cmd->outfile);
		}
		i++;
	}
}

/*static void	echo_print(t_cmd *cmd, int opt, int i)
{
	int	aux;

	aux = i;
	while (cmd->args[i])
	{
		if (ft_strlen(cmd->args[i]) > 1 && cmd->args[i][0] == '$'
			&& (cmd->args[i][1] == SQUOTE || cmd->args[i][1] == DQUOTE))
			cmd->args[i] = del_leaddol(cmd->args[i]);
		i++;
	}
	del_quotes(cmd->args, 1);*/
//	i = aux;
/*	while (cmd->args[i])
	{
		if (ft_strcmp(cmd->args[i], "$?") == 0)
		{
			free(cmd->args[i]);
			cmd->args[i] = ft_itoa(g_exst);
		}
		i++;
	}
	echo_args(cmd, opt, i);
}*/

int	ft_echo(t_cmd *cmd)
{
	int		i;
	int		opt;

	i = 1;
	opt = 0;
	if (dbl_len(cmd->args) == 1)
	{
		if (cmd->args[0][0] != '$' && cmd->infile != 0)
			printf("\n");
		return (0);
	}
	else if (cmd->args[i] && is_nopt(cmd->args[i]))
	{
		opt = 1;
		i++;
	}
	while (cmd->args[i] && is_nopt(cmd->args[i]))
		i++;
	echo_print(cmd, opt, i);
	if (cmd->outfile > 2)
		close (cmd->outfile);
	return (0);
}
