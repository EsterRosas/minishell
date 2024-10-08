/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 18:09:01 by erosas-c          #+#    #+#             */
/*   Updated: 2024/04/01 13:10:57 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

t_prompt	*ft_parse(char *line, t_envv *o_envp)
{
	t_prompt	*prompt;
	char		**lex;

	lex = cmdsubsplit(cmdtrim(line));
	if (!lex)
	{
		g_exst = 0;
		return (NULL);
	}
	prompt = ft_calloc(sizeof(t_prompt), 1);
	if (!prompt)
		return (NULL);
	prompt->envp = o_envp;
	prompt->cmd = get_cmdlst(lex, prompt->envp);
	if (!prompt->cmd || (cmdlistsize(prompt->cmd) == 1 && !prompt->cmd->args[0]
			&& prompt->cmd->hdoc == 1))
	{
		free(prompt);
		return (NULL);
	}
	return (prompt);
}

/* Starts the prompt to the user and reads the input (line).
 * IF !line it's because the user pressed Ctrl+D
  */
void	loop_prompt(t_envv *o_envp)
{
	char		*line;
	t_prompt	*prompt;

	while (1)
	{
		line = readline("minishell~ ");
		if (!line)
			ft_exit(NULL);
		else if (line[0] != '\0' && !only_sp(line))
		{
			prompt = ft_parse(line, o_envp);
			if (prompt)
			{
				ft_exec(prompt);
				free_cmdlist(prompt->cmd);
				free(prompt);
			}
		}
		if (ft_strcmp(line, ""))
			add_history(line);
		free(line);
	}
	return ;
}
