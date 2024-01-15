/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 19:05:44 by erosas-c          #+#    #+#             */
/*   Updated: 2024/01/15 16:53:07 by erosas-c         ###   ########.fr       */
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
