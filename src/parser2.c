/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 20:32:13 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/27 20:48:29 by erosas-c         ###   ########.fr       */
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

char	*fill_path(char *path, t_envv *env_lst, char *first_arg)
{
	char	**path_vls;
	int		i;
	char	*aux;

	i = 0;
	path_vls = get_ptharr(env_lst);
	while (path_vls[i])
	{
		aux = ft_strjoin(path_vls[i], "/");
		path = ft_strjoin(aux, first_arg);
		free(aux);
		if (access(path, F_OK) == 0)
			break ;
		else
		{
			if (path)
				free(path);
			path = NULL;
			i++;
		}
	}
	free_all(path_vls, dbl_len(path_vls));
	return (path);
}
