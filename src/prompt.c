/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 18:09:01 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/19 15:25:02 by damendez         ###   ########.fr       */
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
	prompt = malloc(sizeof(t_prompt));
	if (!prompt)
		return (NULL);
	prompt->cmd = get_cmdlst(lex, o_envp);
	if (!prompt->cmd || (!prompt->cmd->args[0] && prompt->cmd->hdoc == 1))
	{
		free (prompt);
		return (NULL);
	}
	prompt->envp = o_envp;

	
/*	t_cmd		*aux;
	int	i = 0;
	int j = 0;
	aux = prompt->cmd;
	while (aux)
	{
		printf("%i AUX = PROMPT->CMD promt->cmd->in: %i, prompt->cmd->out: %i, \
prompt->cmd->fl_p: %s\n", j, aux->infile, aux->outfile, aux->full_path);
		while (aux->args[i])
		{
			printf("AUX prompt->cmd->args[%i]: %s\n", i, aux->args[i]);
			i++;
		}
		i = 0;
		aux = aux->next;
		j++;
	}*/

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
