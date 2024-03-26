/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 19:07:58 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/26 13:30:16 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**get_ptharr(t_envv *aux)
{
	char	**ptharr;

	ptharr = NULL;
	while (aux && ft_strcmp(aux->nm, "PATH") != 0)
		aux = aux->next;
	if (aux && ft_strcmp(aux->nm, "PATH") == 0)
		ptharr = ft_split(aux->val, ':');
	return (ptharr);
}

void	cmdlst_addback(t_cmd *cmdlst, t_cmd *new)
{
	if (cmdlst == 0)
		cmdlst = new;
	else
	{
		if (!cmdlst)
			return ;
		while (cmdlst->next)
			cmdlst = cmdlst->next;
	}
	cmdlst->next = new;
}

void	free_cmdlist(t_cmd *head)
{
	t_cmd	*current;
	t_cmd	*nextnode;

	current = head;
	while (current)
	{
		nextnode = current->next;
		free_all(current->args, dbl_len(current->args));
		if (current->full_path)
			free(current->full_path);
		if (current->infile > 2)
			close(current->infile);
		if (current->outfile > 2)
			close(current->outfile);
		free(current);
		current = nextnode;
	}
}

void	free_envlist(t_envv *head)
{
	t_envv	*current;
	t_envv	*nextnode;

	current = head;
	while (current)
	{
		nextnode = current->next;
		if (current->nm)
			free(current->nm);
		if (current->val)
			free(current->val);
		free(current);
		current = nextnode;
	}
}

void	ft_globalfree(t_prompt *prompt)
{
	free_envlist(prompt->envp);
	free_cmdlist(prompt->cmd);
	free_all(prompt->path, dbl_len(prompt->path));
	free(prompt);
}
