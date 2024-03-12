/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 18:09:01 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/12 18:41:33 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	upd_shlvl(t_envv *env)
{
	t_envv	*aux;
	char	*tmp;

	aux = env;
	while (aux && ft_strcmp("SHLVL", aux->nm) != 0)
		aux = aux->next;
	if (ft_strcmp("SHLVL", aux->nm) == 0)
	{
		tmp = ft_itoa(ft_atoi(aux->val) + 1);
		free(aux->val);
		aux->val = ft_strdup(tmp);
		free(tmp);
	}
	return (0);
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

/* I thought if non-existing command (args[0]) it would get execve and launch
 * the error >> BUT IT DOESN'T behave this way. We'll have to code this
 * IF !is_builtin(args[0]) && full_ path = NULL
 */
t_prompt	*ft_parse(char *line, t_envv *o_envp)
{
	t_prompt	*prompt;

	prompt = malloc(sizeof(t_prompt));
	if (!prompt)
		return (NULL);
	prompt->cmd = get_cmdlst(line, o_envp);
	if (!prompt->cmd)
	{
		free (prompt);
		return (NULL);
	}
	prompt->envp = o_envp;
	/*t_cmd		*aux;
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
 * ELSE IF: if the user presses Enter or only spaces + Enter, the program does
 * not process the line and shows minishell~ again to the user in a new line.
 */
void	loop_prompt(t_envv *o_envp)
{
	char		*line;
	t_prompt	*prompt;

	while (1)
	{
		line = readline("minishell~ ");
		if (!line)
			ft_exit(1, NULL);
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
		add_history(line);
		free(line);
	}
	return ;
}
