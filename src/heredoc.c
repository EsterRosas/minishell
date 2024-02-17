/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 19:08:13 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/17 13:55:55 by erosas-c         ###   ########.fr       */
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

static char	*get_hdocinput(char *delim)
{
	static char	*input;
	char		*res;
	char		*eol;
	char		*aux2;

	eol = ft_str_eol();
	res = NULL;
	input = NULL;
	ft_signal(2);
	input = readline("> ");
	if (!input)
		return (NULL);
	while (ft_strcmp(input, delim) != 0)
	{
		if (!input)
			return (NULL);
		if (!res)
			res = ft_strdup(input);
		else
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
	free(input);
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
	if (id == 0)
		res = get_hdocinput(delim);
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		wait(NULL);
		ft_signal(1);
	}
	if (!last)
	{
		free(res);
		res = NULL;
	}
	return (res);
}
