/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 18:09:01 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/01 18:32:53 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_status = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}*/

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
	//	signal(SIGINT, handle_sigint);
	//	signal(SIGQUIT, SIG_IGN);
	/*	if (line[0] == '\n')  //intento que si l'usuari posa ENTER toni a llegir rl_gets...i mostrar minishell~
		{
			loop_prompt(char 
		}	*/
		test(line, o_envp);
		line = rl_gets(line);
	}
	if (ft_strcmp(line, "exit") == 0)
		ft_exit();
	free(line);
	return ;
}
