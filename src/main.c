/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:38:52 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/28 17:37:33 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	add_node(char *evar, t_envv *env_lst)
{
	t_envv	*node;
	int		pos;

	pos = 0;
	node = ft_calloc(sizeof(t_envv), 1);
	if (!node)
		return (1);
	if (ft_strchr(evar, '='))
	{
		pos = ft_strchr(evar, '=') - evar;
		node->nm = ft_substr(evar, 0, pos);
		if (ft_strcmp(node->nm, "OLDPWD") == 0)
			node->val = NULL;
		else
			node->val = ft_substr(evar, pos + 1, ft_strlen(evar) - pos - 1);
	}
	else
	{
		node->nm = evar;
		node->val = NULL;
	}
	node->next = NULL;
	add_env_back(env_lst, node);
	return (0);
}

t_envv	*cp_envp(char **envp)
{
	t_envv	*env_lst;
	int		i;

	i = 0;
	env_lst = ft_calloc(sizeof(t_envv), 1);
	if (!env_lst)
		return (NULL);
	env_lst->nm = "";
	env_lst->val = NULL;
	env_lst->next = NULL;
	while (i < dbl_len(envp))
	{
		add_node(envp[i], env_lst);
		i++;
	}
	return (env_lst);
}

int	main(int argc, char **argv, char **envp)
{
	t_envv	*env_lst;

	g_exst = 0;
	env_lst = cp_envp(envp);
	(void)argv;
	(void)argc;
	disable_ctrl_chars();
	ft_signal(1);
	loop_prompt(env_lst);
	free_env(env_lst);
	restore_terminal_settings();
	return (0);
}
