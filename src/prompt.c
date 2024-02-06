/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 18:09:01 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/06 17:53:28 by erosas-c         ###   ########.fr       */
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

/* I thought if non-existing command (args[0]) it would get execve and launch
 * the error >> BUT IT DOESN'T behave this way. We'll have to code this
 * IF !is_builtin(args[0]) && full_ path = NULL
 */
void	ft_parse(char *line, t_envv *o_envp)
{
	int			i;
	t_prompt	*prompt;
	t_cmd		*aux;

	i = 0;
	prompt = malloc(sizeof(t_prompt));
	if (!prompt)
		return ;
	prompt->cmd = get_cmdlst(line, o_envp);
	prompt->envp = env_lst2arr(o_envp);
	aux = prompt->cmd;
	while (aux)
	{
		printf("AUX = PROMPT->CMD promt->cmd->in: %i, prompt->cmd->out: %i, \
prompt->cmd->append: %i, prompt->cmd->fl_p: %s, \
prompt->cmd->hdoc: %s\n", aux->infile, aux->outfile, aux->append, \
aux->full_path, aux->hdoc);
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

/* Starts the prompt to the user and reads the input (line).
 * IF !line it's because the user perssed Ctrl+D
 * ELSE IF: if the user presses Enter or only spaces + Enter, the program does
 * not process the line and shows minishell~ again to the user in a new line.
 */
void	loop_prompt(t_envv *o_envp)
{
	char	*line;

	while (1)
	{
		line = readline("minishell~ ");
		if (!line)
			break ;
		else if (line[0] != '\0' && !only_sp(line))
			ft_parse(line, o_envp);
		add_history(line);
		free(line);
	}
	return ;
}
