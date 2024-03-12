/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:47:25 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/12 21:40:19 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	has_nonum(char *s)
{
	size_t	i;
	i = 0;

	while (s[i] && (s[i] < '0' || s[i] > '9'))
		i++;
	if (ft_strlen(s) == 2 && s[0] == '-' && s[1] == '-')
		return (0);
	else if (i == ft_strlen(s))
		return (1);
	return (0);
}

static int	custom_atoi(char *s)
{
	int			i;
	int			sign;
	long long	num;

	num = 0;
	i = 0;
	sign = 1;
	if (ft_strlen(s) > 20 || s[0] == '\0' || has_nonum(s)
		|| (ft_strlen(s) == 19 && ft_strncmp("9223372036854775807", s, 20) < 0)
		|| (ft_strlen(s) == 20 && ft_strncmp("-9223372036854775807", s, 21) < 0))
	{
		write(2, "exit\n", 5);
		handle_error_opt("exit", s, "numeric argument required");
		exit (255);
	}
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		num = num * 10 + s[i] - '0';
		i++;
	}
	return (num * sign);
}

static char	*del_spaces(char *s)
{
	char *res;
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(s) - 1;
	res = NULL;
	while (s[i] && (s[i] == ' ' || s[i] == '\r' || s[i] == '\t' || s[i] == '\n'
		|| s[i] == '\v' || s[i] == '\f'))
		i++;
	while (s[j] && (s[j] == ' ' || s[j] == '\r' || s[j] == '\t' || s[j] == '\n'
		|| s[j] == '\v' || s[j] == '\f'))
		j--;
	j++;
	res = ft_substr(s, i, j - i);
	free(s);
	return (res);
}

static int	check_num(char *s)
{
	int	i;

	i = 0;
	if (s[i] && (s[i] == '+' || s[i] == '-'))
		i++;
	if (ft_strlen(s) == 2 && s[0] == '-' && s[1] == '-')
		return (1);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
		{
			write(2, "exit\n", 5);
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

	/*if (args)
		printf("dbl_len(args): %i\n", dbl_len(args));*/
	n = 0;
	if (args && args[1] && !has_nonum(args[1]))
		args[1] = del_spaces(args[1]);
	if (!args || dbl_len(args) == 1)
	{
		if (print == 1)
			printf("exit\n");
		g_exst = 0;
	}
	else if (check_num(args[1]) && args[2])
	{
		write(2, "exit\n", 5);
		handle_error("exit", "too many arguments");
		return (1);
	}
	else
	{
		n = custom_atoi(args[1]);
		g_exst = (unsigned char)n;
//		printf("MIDDLE g_exst: %i\n", g_exst);
		write(2, "exit\n", 5);
		//printf("exit\n");
	}
	restore_terminal_settings();
//	printf("END g_exst: %i\n", g_exst);
	exit (g_exst);
}
