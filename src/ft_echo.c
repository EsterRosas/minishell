/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:51:09 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/26 11:22:19 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*char	*get_ex_st(char *s)
{
	char	*res;

	res = ft_itoa(g_exst);
	free(s);
	return (res);
}*/

int	ft_echo(t_cmd *cmd)
{
	int		i;

	i = 0;
	if (dbl_len(cmd->args) == 1 && cmd->infile == 0)
	{
		printf("\n");
		return (0);
	}
	else if (cmd->args[1] && ft_strcmp(cmd->args[1], "-n") == 0)
		i++;
	while (cmd->args[++i])
	{
		if (ft_strcmp(cmd->args[i], "$?") == 0)
			cmd->args[i] = ft_itoa(g_exst);
		ft_putstr_fd(cmd->args[i], cmd->outfile);
		if (i < dbl_len(cmd->args) - 1)
			ft_putstr_fd(" ", cmd->outfile);
		else if (ft_strcmp(cmd->args[1], "-n") != 0)
			ft_putstr_fd("\n", cmd->outfile);
	}
	if (cmd->outfile > 2)
		close (cmd->outfile);
	return (g_exst);
}
