/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 20:39:32 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/13 19:59:37 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* This functions prevents the control chars (^C & ^\)to be shown in the
 * terminal. By default those ctrl chars are shown in the terminal when the
 * user presses Ctrl+C & Ctrl+\, respectively (signals)). This is done by
 * setting the ECHOCTL flag (an attribute of the terminal), through the termios
 * library.
 */
void	disable_ctrl_chars(void)
{
	struct termios	new_termios;

	tcgetattr(0, &new_termios);
	new_termios.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &new_termios);
}

/* Sets the terminal attributes back to their original (default) setting.
 */
void	restore_terminal_settings(void)
{
	struct termios	new_termios;

	tcgetattr(0, &new_termios);
	new_termios.c_lflag |= ECHOCTL;
	tcsetattr(0, TCSANOW, &new_termios);
}

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
		g_exst = 130;
	else if (sig == SIGQUIT)
	{
		write(1, "Quit: 3\n", 10);
		g_exst = 131;
	}
	return ;
}

/* This function can be called either from the parent process or from a child.
 * Use i = 1 from the parent, and i = 0 from any child.
 */
void	ft_signal(int i)
{
	struct sigaction	sa;

	if (i)
		sa.sa_handler = &parent_handler;
	else
		sa.sa_handler = &child_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL); //Ctrl+C
	sigaction(SIGQUIT, &sa, NULL); //Ctrl+contrabarra
	sigaction(SIGTERM, &sa, NULL);

}
