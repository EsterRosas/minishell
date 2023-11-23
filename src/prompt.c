/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 18:09:01 by erosas-c          #+#    #+#             */
/*   Updated: 2023/11/23 19:15:15 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/defines.h"
#include "../lib/libft/libft.h"

static int	ft_strcmp(char *s1, char *s2)
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

void	loop_prompt(char *line)
{
	if (line == NULL)
	{
		line = rl_gets(line);
		//ft_echo(line);
		test(line);
	}
	while (ft_strcmp(line, "exit") != 0)
	{
		line = rl_gets(line);
	//	ft_echo(line);
		test(line);
	}
	free(line);
	return ;
}
