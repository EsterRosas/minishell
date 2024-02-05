/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 18:09:01 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/05 21:24:51 by erosas-c         ###   ########.fr       */
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

void	ft_parse(char *line, t_envv *o_envp)
{
	int			i;
	t_prompt	*prompt;
	t_cmd		*aux;

	i = 0;
	prompt = malloc(sizeof(t_prompt));
	if (!prompt)
		return ;
	/* If non-existing command (args[0]) it will get execve and it will launch
	 * the error >> doncs no, no es aixi, ho haurem de forcar si path = NULL
	 */
	prompt->cmd = get_cmdlst(line, o_envp);
	prompt->envp = env_lst2arr(o_envp);
	aux = prompt->cmd;
	while (aux)
	{
		printf("AUX = PROMPT->CMD promt->cmd->in: %i, prompt->cmd->out: %i, prompt->cmd->append: %i, \
prompt->cmd->fl_p: %s, prompt->cmd->hdoc: %s\n", aux->infile, aux->outfile, aux->append, aux->full_path, aux->hdoc);
		while (aux->args[i])
		{
			printf("AUX prompt->cmd->args[%i]: %s\n", i, aux->args[i]);
			i++;
		}
		i = 0;
		aux = aux->next;
	}
	free_cmdlist(prompt->cmd);
	free_all(prompt->envp, dbl_len(prompt->envp));
	free(prompt);
}

void	loop_prompt(/*char *line,*/t_envv *o_envp)
{
	char	*line;

	while (1)
	{
		line = readline("minishell~ ");
		if (!line) //this is the case when the user hits Ctrl+D
			break ;
		else if (line[0] != '\0' && !only_sp(line))  //si l'usuari prem ENTER o nomes espais, no processa la line i mostra de nou minishell~
			ft_parse(line, o_envp);
		add_history(line);
	//	if (line)
		free(line);
	}
	return ;
}
