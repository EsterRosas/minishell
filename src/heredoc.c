/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 19:08:13 by erosas-c          #+#    #+#             */
/*   Updated: 2024/01/30 20:59:17 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* NOTA: el heredoc ha de tenir els seus propis senyals
 *
 *
 */

char	*process_hdoc(char *delim, int last)
{
	static char	*input;
	char		*res;
	char		*line_end;

	line_end = malloc(sizeof(char) + 1);
	line_end[0] = '\n';
	line_end[1] = '\0';
	res = NULL;
	input = readline("> ");
	while (ft_strcmp(input, delim) != 0)
	{
		if (last && res == NULL)
			res = ft_strdup(input);
		else if (last)
			res = ft_strjoin(res, input);
		if (res)
			res = ft_strjoin(res, line_end);
		input = readline("> ");
	}
	return (res);
}
