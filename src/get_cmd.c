/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:46:17 by damendez          #+#    #+#             */
/*   Updated: 2024/02/06 20:22:45 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void exec_ext_cmd(t_prompt  *prompt)
{
    pid_t   pid;

    pid = fork();
    if (pid == -1)
        handle_error("fork error");
    else if (!pid)
    {
        printf("Hello from child process");
        if (execve(prompt->cmd->full_path, prompt->cmd->args, env_lst2arr(prompt->envp)) == -1)
            handle_error("execve error");
        exit(EXIT_SUCCESS);
    }
    else
    {
        waitpid(pid, NULL, 0);
    }
}
