/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:51:09 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/10 20:10:33 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_echo(t_cmd *cmd)
{
	int		i;

	i = 0;
	if (dbl_len(cmd->args) == 1)
	{
		printf("\n");
		return ;
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
}
