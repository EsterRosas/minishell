/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 20:32:13 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/08 18:28:28 by erosas-c         ###   ########.fr       */
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

t_cmd	fill_cmdlst(char **lex, t_envv *env_lst, t_cmd *cmdlst, int cmd_n)
{
	int		i;
	t_cmd	*new;

	i = 0;
	while (++i < cmd_n)
	{
		while (*lex && *lex[0] != '|')
			lex++;
		if (*lex && *lex[0] == '|')
		{
			lex++;
			if (cmdlst == NULL)
			{
				printf("fill_cmdlst: cmdlst should be NULL: %p\n", cmdlst);
				cmdlst = get_cmd(lex, env_lst);
				printf("fill_cmdlst (parser2) cmdlst: %p\n", cmdlst);
			}
			else
			{
				new = get_cmd(lex, env_lst);
				cmdlst_addback(cmdlst, new);
			}
		}
	}
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
		if (current->hdoc)
			free(current->hdoc);
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
