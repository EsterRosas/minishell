/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 19:08:13 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/15 19:05:27 by erosas-c         ###   ########.fr       */
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

static char	*get_hdocinput(char *delim, int last)
{
	static char	*input;
	char		*res;
	char		*eol;
	char		*aux2;

	eol = ft_str_eol();
	res = NULL;
	input = readline("> ");
	ft_signal(0);
	if (last)
		res = ft_strdup(input);
	if (!input)
		return (NULL);
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

char	*process_hdoc(char *delim, int last)
{
	char		*res;
	int			id;

	res = NULL;
	id = fork();
	if (id == -1)
	{
		printf("minishell: %s\n", strerror(errno));
		return (NULL);
	}	
	if (id != 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
//		signal(SIGTERM, SIG_IGN);
		wait(NULL);
		ft_signal(1);
	}
	else
	{
		restore_terminal_settings();
		res = get_hdocinput(delim, last);
		disable_ctrl_chars();
	}
	return (res);
}
