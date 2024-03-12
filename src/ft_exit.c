/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:47:25 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/12 10:48:50 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	check_num(char *s)
{
	int	i;

	i = 0;
	if (s[i] && (s[i] == '+' || s[i] == '-'))
		i++;
	while (s[i])
	{
		if (ft_strlen(s) > 20 || (ft_strlen(s) == 20 && s[0] != '-'
			&& s[0] != '+') || (s[i] < '0' || s[i] > '9'))
		{
			printf("exit\n");
			handle_error_opt("exit", s, "numeric argument required");
			exit (255);
		}
		i++;
	}
	return (0);
}

int	ft_exit(int print, char **args)
{
	if (!args || dbl_len(args) == 1)
	{
		if (print == 1)
			printf("exit\n");
		g_exst = 0;
	}
	else if (check_num(args[1]) == 0 && args[2])
	{
		handle_error("exit", "too many arguments");
		return (1);
//		if check_rang/ comprovar aquí en cas que surti del rang
	}
/*	else
		g_exst = ft_itoa(args[1]);*/
	restore_terminal_settings();
	exit (g_exst);
}
