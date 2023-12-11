/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 19:05:44 by erosas-c          #+#    #+#             */
/*   Updated: 2023/12/11 21:54:54 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	assign_infile(char	*file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	//if the file doesn't exist yet, now its returning the error, but we should
	//create it instead
	if (fd == -1)
	{
		printf("Error opening file %s\n", file);
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
		printf("Error opening file %s\n", file);
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
	while (cmd_n > 0)
	{
		if (cmd->full_path)
			free(cmd->full_path);
		free(&cmd[cmd_n - 1]);
		cmd_n--;
	}
}
