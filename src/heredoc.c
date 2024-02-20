/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 19:08:13 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/20 21:20:43 by erosas-c         ###   ########.fr       */
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
static char *feed_hdoc(char *res, char	*input)
{
	char	*eol;
	char	*aux;

	eol = ft_str_eol();
	if (!res)
	{
		aux = ft_strdup(input);
		res = ft_strjoin(input, eol);
		free(aux);
	}
	else
	{
		aux = ft_strjoin(res, input);
		free(res);
		res = ft_strjoin(aux, eol);
		free(aux);
	}
	free(eol);
	return (res);
}

static char	*read_input(char *input, char *delim)
{
	char	*res;
//	char	*eol;
//	char	*aux;

//	eol = ft_str_eol();
	res = NULL;
	while (ft_strcmp(input, delim) != 0)
	{
		if (!input)
			exit (1);
		res = feed_hdoc(res, input);
	/*	if (!res)
		{
			aux = ft_strdup(input);
			res = ft_strjoin(input, eol);
			free(aux);
		}
		else
		{
			aux = ft_strjoin(res, input);
			free(res);
			res = ft_strjoin(aux, eol);
			free(aux);
		}*/
		free(input);
		input = readline("> ");
	}
	free(input);
//	printf("res heredoc: %s\n", res);
	return (res);
}

static void	get_input(char *delim, int *fd)
{
	static char	*input;
	char		*res;

	close(fd[R_END]);
	ft_signal(2);
	input = readline("> ");
	if (!input)
		exit (1);
	res = read_input(input, delim);
	if (write(fd[W_END], res, ft_strlen(res)) == -1)
		printf("minishell: %s\n", strerror(errno));
	return ;
}

static int	do_fork(char *delim, int *fd)
{
	int	id;

	id = make_fork();
	if (id == 0)
	{
		get_input(delim, fd);
		exit (1);
	}
	else
	{
		close(fd[W_END]);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		wait(NULL);
		ft_signal(1);
	}
	return (fd[R_END]);
}

int	process_hdoc(char *delim, int last)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		printf("minishell: %s\n", strerror(errno));
		return (-1); //segur??
	}
	do_fork(delim, fd);
	if (!last)
	{
		close(fd[R_END]);
		return (0);
	}
	return (fd[R_END]);
}
