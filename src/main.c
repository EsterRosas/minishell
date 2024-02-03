/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:38:52 by erosas-c          #+#    #+#             */
/*   Updated: 2024/01/15 20:49:10 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	static char	*line;
	t_envv		*env_lst;

	env_lst = cp_envp(envp);
	(void)argv;
	(void)argc;
	line = NULL;
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	loop_prompt(line, env_lst);
	free_env(env_lst);
	return (0);
}
/*
int main() {
    FILE *file = fopen("nonexistentfile.txt", "r");

    if (file == NULL) {
        handle_error("Failed to open file");
    }

    // Rest of your code
    return 0;}*/
