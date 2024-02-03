/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 18:09:01 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/03 12:35:37 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
//		g_exst = 1;
	}
/*	else if (sig == SIGQUIT)
	{
	POTSER BUSCAR IGNORE SIGNALS FUNCTION
		write(1, "Quit: 3\n", 10);
		g_exst = 131;
	}*/
	return ;
}

int	only_sp(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] == KSPACE)
		i++;
	if (!s[i])
		return (1);
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

char	*rl_gets(char *line)
{
	if (line)
	{
		free(line);
		line = NULL;
	}
	line = readline("minishell~ ");
	if (line && *line)
		add_history(line);
	return (line);
}

/*void	loop_prompt(char *line, t_envv *o_envp)
{
	if (line == NULL)
	{
		line = rl_gets(line);
		test(line, o_envp);
	}
	while (ft_strcmp(line, "exit") != 0)
	{
		line = rl_gets(line);
		test(line, o_envp);
	}
	if (ft_strcmp(line, "exit") == 0)
		ft_exit();
	free(line);
	return ;
}*/

void	loop_prompt(char *line, t_envv *o_envp)
{
	if (line == NULL)
		line = rl_gets(line);
	while (ft_strcmp(line, "exit") != 0)
	{
	//	signal(SIGQUIT, SIG_IGN);
	//	a l'IF seguent falta afegir Ctrl-C: ara surt i hem de fer que no faci res, com BASH
		if (line[0] != '\0' && !only_sp(line))  //si l'usuari prem ENTER no processa la line i mostra de nou minishell~
			test(line, o_envp);
		line = rl_gets(line);
	}
	if (ft_strcmp(line, "exit") == 0) // aqui hem de posar tb la condicio de si es Ctrl-D (tb printa "exit")
		ft_exit();
	free(line);
	return ;
}
