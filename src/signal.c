/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 20:39:32 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/27 19:55:57 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	parent_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_exst = 1;
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

static void	child_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		g_exst = 130;
		exit (130);
	}
	else if (sig == SIGQUIT)
	{
		write(1, "Quit: 3\n", 10);
		g_exst = 131;
		exit (131);
	}
	return ;
}

static void	heredoc_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		g_exst = 1;
		exit (1);
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

/* This function can be called either from the parent process or from a child.
 * Use i = 1 from the parent, and i = 0 from any child.
 * Adding 2 for heredoc.
 */
void	ft_signal(int i)
{
	struct sigaction	sa;

	if (i == 1)
		sa.sa_handler = &parent_handler;
	else if (i == 0)
		sa.sa_handler = &child_handler;
	else
		sa.sa_handler = &heredoc_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
}
