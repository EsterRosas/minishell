/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 19:08:13 by erosas-c          #+#    #+#             */
/*   Updated: 2024/01/31 18:33:14 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* NOTA: el heredoc ha de tenir els seus propis senyals
 */

char	*process_hdoc(char *delim, int last)
{
	static char	*input;
	char		*res;
	char		*eol;
	char		*aux2;

	eol = malloc(sizeof(char) + 1);
	eol[0] = '\n';
	eol[1] = '\0';
	res = NULL;
	if (last)
		res = ft_strdup(input);
	input = readline("> ");
	while (ft_strcmp(input, delim) != 0)
	{
		if (last)
		{
			aux2 = ft_strjoin(res, input);
			free(res);
			res = ft_strjoin(aux2, eol);
			free(aux2);
		}
		free(input);
		input = readline("> ");
	}
	free(eol);
	return (res);
}
