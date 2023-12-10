/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 19:05:44 by erosas-c          #+#    #+#             */
/*   Updated: 2023/12/10 21:31:37 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	assign_infile(char	*file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("Error opening file %s", file);
		return (-1);
	}
	else
		return (fd);
}

int	assign_outfile(char	*file)
{
	int	fd;

	fd = open(file, O_WRONLY);
	if (fd == -1)
	{
		printf("Error opening file %s", file);
		return (-1);
	}
	else
		return (fd);
}

void	free_cmds(char **lexed, t_cmd *cmd)
{
	int	i;
	int	cmd_n;

	i = 0;
	cmd_n = 1;
	while (i < dbl_len(lexed))
	{
		if (lexed[i][0] == '|')
			cmd_n++;
			i++;
	}
	printf("cmd_n: %i\n", cmd_n);
	while (cmd_n > 0)
	{
		free(&cmd[cmd_n - 1]);
		cmd_n--;
	}
}

