/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:47:25 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/24 17:50:17 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	check_scope(char *s)
{
	if (ft_strlen(s) > 20 || s[0] == '\0' || has_nonum(s)
		|| (ft_strlen(s) == 19 && ft_strncmp("9223372036854775807", s, 20) < 0)
		|| (ft_strlen(s) == 20
			&& ft_strncmp("-9223372036854775808", s, 21) < 0))
	{
		write(2, "exit\n", 5);
		handle_error_opt("exit", s, "numeric argument required");
		exit (255);
	}
}

static int	custom_atoi(char *s)
{
	int			i;
	int			sign;
	long long	num;

	num = 0;
	i = 0;
	sign = 1;
	check_scope(s);
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
	char	*res;
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
	while (s[i] && s[i + 1] && s[i] == '0' && s[i + 1] == '0')
		i++;
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

int	ft_exit(t_cmd *cmd, t_prompt *prompt)
{
	int	n;

	n = 0;
	g_exst = 0;
	if (cmd && cmd->args && cmd->args[1] && !has_nonum(cmd->args[1]))
		cmd->args[1] = del_spaces(cmd->args[1]);
	if (!cmd || !cmd->args || dbl_len(cmd->args) == 1)
		printf("exit\n");
	else if (check_num(cmd->args[1]) && cmd->args[2])
	{
		write(2, "exit\n", 5);
		handle_error("exit", "too many arguments");
		if (prompt)
			ft_globalfree(prompt);
		return (1);
	}
	else if (!cmd->next)
	{
		n = custom_atoi(cmd->args[1]);
		g_exst = (unsigned char)n;
		printf("exit\n");
	}
	restore_terminal_settings();
	//system("leaks minishell");  // esborrar al final
	exit (g_exst);
}
