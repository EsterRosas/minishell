/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:47:25 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/08 20:48:26 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_exit(int print)
{
	if (print == 1)
		printf("exit\n");
	g_exst = 0;
	restore_terminal_settings();
	exit (g_exst);
}
