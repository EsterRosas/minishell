/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:51:09 by erosas-c          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/03/17 02:08:17 by erosas-c         ###   ########.fr       */
=======
/*   Updated: 2024/03/17 17:13:43 by erosas-c         ###   ########.fr       */
>>>>>>> master
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
	if (!cmd->args[i] && opt == 0 && cmd->outfile != 1)
		ft_putstr_fd("\n", cmd->outfile);
	else
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
}

int	ft_echo(t_cmd *cmd)
{
	int		i;
	int		opt;

	i = 1;
	opt = 0;
	if (dbl_len(cmd->args) == 1)
	{
<<<<<<< HEAD
		if (cmd->args[0][0] != '$' && (cmd->infile == 0 || !cmd->hdoc))
=======
		if (cmd->args[0][0] != '$' && (cmd->infile == 0 || !cmd->hdoc)
			&& cmd->outfile == 1)
		{
>>>>>>> master
			printf("\n");
			return (0);
		}
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
