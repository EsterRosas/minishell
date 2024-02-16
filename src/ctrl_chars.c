/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_chars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:00:57 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/16 18:01:07 by erosas-c         ###   ########.fr       */
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
