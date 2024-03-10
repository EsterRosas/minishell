/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 19:08:13 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/10 18:16:26 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* NOTA: el heredoc ha de tenir els seus propis senyals
 * pq si estem a mig "demanar input heredoc a usuari", si es fa Ctr+C
 * o altres, surt del heredoc, pero no del minishell, per aixo heredoc s'ha
 * d'executar en un proces a part (child).
 */
static char	*feed_hdoc(char *res, char	*input, char *eol)
{
	char	*aux;
	
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
	printf("res: %s\n", res);
	return (res);
}

/* While the input written by the user is not the DELIMITER (EOF or similar,
 * usually), we go getting user input and joining all input received. Each
 * line followed by a "\n" (eol)
 *
 * That's why at the end we take the substring not including last cgar (\n).
 */
static char	*read_input(char *input, char *delim, char *eol)
{
	char	*res;
	char	*aux;

	aux = NULL;
	res = NULL;
	if (ft_strcmp(input, delim) == 0)
		return (eol);
	while (ft_strcmp(input, delim) != 0)
	{
		if (!input)
		{
			free(aux);
			exit (0);
		}
		aux = feed_hdoc(aux, input, eol);
		free(input);
		input = readline("> ");
	}
	free(input);
	res = ft_substr(aux, 0, ft_strlen(aux) - 1);
	free(aux);
	return (res);
}

/* When we start the heredoc itself (showing '> ' to the user for them to input
 * the content they want, first we close the READ END of the pipe, because
 * we will not need it in the child process.
 *
 * We enable the ft_signal with a parameter not 0 and not 1, which calls the
 * heredoc signal handler.
 *
 * Show '> ' to the user so to collect the input. If user presses Ctrl+D
 * (not a signal) this means theres no input (!input), we have to exit the
 * heredoc (not the minishell) as in Bash.
 *
 * If the user writes some input, we get it through the function read_input.
 *
 * Once we got it, we write it to the WRITE END of the pipe, so it will be ready
 * to be read from the parent process, as the pipe was created before the fork
 */
static void	get_input(char *delim, int *fd)
{
	static char	*input;
	char		*res;
	char		*eol;

	eol = malloc(sizeof(char) + 1);
	if (!eol)
		return ;
	eol[0] = '\n';
	eol[1] = '\0';
	close(fd[R_END]);
	ft_signal(2);
	input = readline("> ");
	if (!input)
		exit (0);
	res = read_input(input, delim, eol);
	if (write(fd[W_END], res, ft_strlen(res)) == -1)
		printf("minishell: %s\n", strerror(errno));
	return ;
}

/* We do the fork.
 *
 * CHILD: we offer "> " to the user to get his input (heredoc) through the
 * get_input function (its parameters are the "delimiter, such as EOF writen
 * by the user right after '<<' and the int *fd that the pipe function
 * returned. Then call exit to exit the child process.
 *
 * PARENT: closes the write end firstly because we will not need it.
 * We ignore the signals through SIG_IGN so to avoid that a signal makes
 * the program to follow the signals as in parent until the child has finished.
 * wait for the CHILD process and then enable again the signals corresponding
 * to the parent (not to the heredoc).
 */
static int	do_fork(char *delim, int *fd)
{
	int	id;
	int	status;

	id = make_fork();
	if (id == 0)
	{
		get_input(delim, fd);
		exit (0);
	}
	else
	{
		close(fd[W_END]);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(id, &status, 0);
//		ft_signal(1);
	}
	if (WIFEXITED(status))
		g_exst = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exst = WTERMSIG(status);
	return (fd[R_END]);
}

/* This function is called from assign_infile function in parser_utils.c file
 * in order to get a file descriptor corresponding to the file where the
 * input content to be used is stored. but only WHEN "<<" separator (heredoc)
 * is found.
 *
 * It creates a pipe so we can ask and get the user input from a child (as
 * the signals in heredoc work in a different way than in the parent process),
 * and save this content to the WRITE END of the pipe and later on readit from
 * the READ END of the pipe in the parent process.
 *
 * In case the "input file" (separator '<' OR '<<' is not the last in the cmd,
 * it closes both ends of the pipe as none of them this will be used as the
 * input to by the cmd, since it always uses the last input file found.
 */
int	process_hdoc(char *delim, int last)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		handle_error("pipe", strerror(errno));
		return (-1);
	}
	do_fork(delim, fd);
	if (!last)
	{
		close(fd[W_END]);
		close(fd[R_END]);
		return (0);
	}
	return (fd[R_END]);
}
