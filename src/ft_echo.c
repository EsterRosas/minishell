/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:51:09 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/16 19:41:07 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_echo(t_cmd *cmd)
{
	int		i;

	i = 0;
	if (dbl_len(cmd->args) == 1)
	{
		printf("\n");
		return (0);
	}
	if (ft_strcmp(cmd->args[1], "-n") == 0)
		i++;
	while (cmd->args[++i])
	{
		ft_putstr_fd(cmd->args[i], cmd->outfile);
		if (i < dbl_len(cmd->args) - 1)
			ft_putstr_fd(" ", cmd->outfile);
		else if (ft_strcmp(cmd->args[1], "-n") != 0)
			ft_putstr_fd("\n", cmd->outfile);
	}
	if (cmd->outfile > 2)
		close (cmd->outfile);
	return (0);	
}
