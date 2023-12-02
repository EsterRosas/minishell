/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:38:52 by erosas-c          #+#    #+#             */
/*   Updated: 2023/12/02 19:24:48 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/defines.h"
#include <fcntl.h>

/*t_envv	*cp_envp(char **envp)
{
	t_envv	*res;
	int		i;
	int		pos;

	i = 0;
	pos = 0;
	res = malloc(sizeof(t_envv) * dbl_len(envp));
	if (!res)
		return (NULL);
	while (envp[i] != NULL)
	{
		pos = ft_strchr(envp[i], '=') - envp[i];
		res[i].nm = ft_substr(envp[i], 0, pos);
		res[i].val = ft_substr(envp[i], pos + 1, ft_strlen(envp[i]) - 1);
		res[i].size = dbl_len(envp);
		i++;
	}
	return (res);
}*/

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
	add_env_back(&env_lst, cmd);
}

t_envv	*cp_envp(char **envp)
{
	t_envv	*env_lst;
//	t_envv	*cmd;
//	int		pos;
	int		i;
	env_lst = NULL;

	i = 0;
//	pos = 0;
	while (i < dbl_len(envp))
	{
		add_node(envp[i], env_lst);
		i++;
/*		cmd = malloc(sizeof(t_envv));
		if (!res)
			return (NULL);
		pos = ft_strchr(envp[i], '=') - envp[i];
		cmd.nm = ft_substr(envp[i], 0, pos);
		cmd.val = ft_substr(envp[i], pos + 1, ft_strlen(envp[i]) - 1);
		env_lst = ft_lstnew(t_envv *cmd);*/
	}
	return (env_lst);
}

int	main(int argc, char **argv, char **envp)
{
	static char	*line;
	t_envv		*env_lst;
	//	t_envv		*o_envp;
//	int i = 0;
	env_lst = cp_envp(envp);	
/*	while (i < dbl_len(o_envp))
	{
		printf("o_envp[%i]: %s\n", i, o_envp[i]);
		i++;
	}*/
	(void)argv;
	(void)argc;
	line = NULL;
	loop_prompt(line, env_lst);
	free_env(&env_lst);
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
