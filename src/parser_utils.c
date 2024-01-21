/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 19:05:44 by erosas-c          #+#    #+#             */
/*   Updated: 2024/01/17 12:45:06 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	assign_infile(char *file)
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

/* NOTE: If the file cannot be opened, it doesn't get to the line where it checks
 * whether its append instead of simple redirection*/
int	assign_outfile(char **lex, int i, bool *append)
{
	int	fd;

	fd = open(lex[i], O_RDWR);
	if (fd == -1)
	{
		printf("Error opening file %s\n", lex[i]);
		return (-1);
	}
	i--;
	if (ft_strlen(lex[i]) == 2 && lex[i][1] == '>')
		*append = true;
	return (fd);
}
