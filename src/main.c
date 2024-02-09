/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:38:52 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/08 18:54:42 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
//		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
//		rl_redisplay();
//		g_exst = 1;
	}
/*	else if (sig == SIGQUIT)
	{
	}*/
	return ;
}

void	add_node(char *evar, t_envv *env_lst)
{
	t_envv	*cmd;
	int		pos;

	cmd = malloc(sizeof(t_envv));
	if (!cmd)
		return ;
	pos = ft_strchr(evar, '=') - evar;
	cmd->nm = ft_substr(evar, 0, pos);
	cmd->val = ft_substr(evar, pos + 1, ft_strlen(evar) - 1);
	cmd->next = NULL;
	add_env_back(env_lst, cmd);
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

	// hey from testing-david :)
	env_lst = cp_envp(envp);
	(void)argv;
	(void)argc;
	signal(SIGINT, handle_signal); //Ctrl+C
	signal(SIGQUIT, handle_signal); //Ctrl+contrabarra
	loop_prompt(env_lst);
	free_env(env_lst);
	return (0);
}
