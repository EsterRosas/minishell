/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:38:52 by erosas-c          #+#    #+#             */
/*   Updated: 2023/11/27 16:37:45 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/defines.h"
#include <fcntl.h>

t_envv	*cp_envp(char **envp)
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
}


int	main(int argc, char **argv, char **envp)
{
	static char	*line;
	t_envv		*o_envp;

	o_envp = cp_envp(envp);
	(void)argv;
	(void)argc;
	line = NULL;
	loop_prompt(line, o_envp);
	free_env(o_envp);
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
