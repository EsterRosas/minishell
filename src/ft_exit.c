/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:47:25 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/12 18:46:44 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	custom_atoi(char *s)
{
	int			i;
	int			sign;
	long long	num;

	num = 0;
	i = 0;
	sign = 1;
	if (ft_strlen(s) > 20
		|| (ft_strlen(s) == 19 && ft_strncmp("9223372036854775807", s, 20) < 0)
		|| (ft_strlen(s) == 20 && ft_strncmp("-9223372036854775807", s, 21) < 0))
	{
		printf("exit\n");
		handle_error_opt("exit", s, "numeric argument required");
		exit (255);
	}
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	i = -1;
	while (s[++i] >= '0' && s[i] <= '9')
		num = num * 10 + s[i] - '0';
	return (num * sign);
}

static int	check_num(char *s)
{
	int	i;

	i = 0;
	if (s[i] && (s[i] == '+' || s[i] == '-'))
		i++;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
		{
			printf("exit\n");
			handle_error_opt("exit", s, "numeric argument required");
			exit (255);
		}
		i++;
	}
	return (1);
}

int	ft_exit(int print, char **args)
{
	int	n;

/*	if (args)
		printf("dbl_len(args): %i\n", dbl_len(args));*/
	n = 0;
	if (!args || dbl_len(args) == 1)
	{
		if (print == 1)
			printf("exit\n");
		g_exst = 0;
	}
	else if (check_num(args[1]) && args[2])
	{
		handle_error("exit", "too many arguments");
		return (1);
	}
	else
	{
		n = custom_atoi(args[1]);
		g_exst = (unsigned char)n;
		printf("exit\n");
	}
	restore_terminal_settings();
	exit (g_exst);
}
