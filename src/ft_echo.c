/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:51:09 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/09 17:51:13 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_echo(t_cmd *cmd)
{
	int		i;

	i = 0;
	if (ft_strcmp(cmd->args[1], "-n") == 0)
		i++;
	while (cmd->args[++i])
	{
		printf("%s", cmd->args[i]);
		if (i < dbl_len(cmd->args) - 1)
			printf(" ");
		else if (/*i == dbl_len(cmd->args) - 1 &&*/ ft_strcmp(cmd->args[1], "-n") != 0)
			printf("\n");
	}
}

