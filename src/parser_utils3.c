/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 19:07:58 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/16 20:29:56 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**get_ptharr(t_envv *env_lst)
{
	char	**ptharr;

	ptharr = NULL;
	while (env_lst && ft_strcmp(env_lst->nm, "PATH") != 0)
		env_lst = env_lst->next;
	if (env_lst && ft_strcmp(env_lst->nm, "PATH") == 0)
		ptharr = ft_split(env_lst->val, ':');
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
