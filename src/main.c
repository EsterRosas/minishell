/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:38:52 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/22 20:58:33 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	add_node(char *evar, t_envv *env_lst)
{
	t_envv	*node;
	int		pos;

	pos = 0;
	node = malloc(sizeof(t_envv));
	if (!node)
		return ;
	if (ft_strchr(evar, '='))
	{
		pos = ft_strchr(evar, '=') - evar;
		node->nm = ft_substr(evar, 0, pos);
		if (ft_strcmp(node->nm, "OLDPWD") == 0)
			node->val = NULL;
		else
			node->val = ft_substr(evar, pos + 1, ft_strlen(evar) - 1);
	}
	else
	{
		node->nm = evar;
		node->val = NULL;
	}
	node->next = NULL;
	add_env_back(env_lst, node);
}

t_envv	*cp_envp(char **envp)
{
	t_envv	*env_lst;
	int		i;

	env_lst = malloc(sizeof(t_envv));
	if (!env_lst)
		return (NULL);
	i = ft_strchr(envp[0], '=') - envp[0];
	env_lst->nm = ft_substr(envp[0], 0, i);
	env_lst->val = ft_substr(envp[0], i + 1, ft_strlen(envp[0]) - 1);
	env_lst->next = NULL;
	i = 1;
	while (i < dbl_len(envp))
	{
		add_node(envp[i], env_lst);
		i++;
	}
	return (env_lst);
}

int	main(int argc, char **argv, char **envp)
{
	t_envv		*env_lst;

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
