/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 19:08:13 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/14 16:57:19 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* NOTA: el heredoc ha de tenir els seus propis senyals
 */

char	*ft_str_eol(void)
{
	char	*res;

	res = malloc(sizeof(char) + 1);
	if (!res)
		return (NULL);
	res[0] = '\n';
	res[1] = '\0';
	return (res);
}

char	*process_hdoc(char *delim, int last)
{
	static char	*input;
	char		*res;
	char		*eol;
	char		*aux2;

	eol = ft_str_eol();
	res = NULL;
	if (last)
		res = ft_strdup(input);
	restore_terminal_settings();
	input = readline("> ");
	if (!input)
		return (NULL);
	while (ft_strcmp(input, delim) != 0)
	{
		ft_signal(0);
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
	disable_ctrl_chars();
	return (res);
}
