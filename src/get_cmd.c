/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:46:17 by damendez          #+#    #+#             */
/*   Updated: 2024/01/17 20:01:12 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void exec_ext_cmd(t_cmd	*current_cmd, t_prompt  *prompt)
{
    pid_t   pid;

    pid = fork();
    if (pid == -1)
        handle_error("fork error");
    else
        if (execve(current_cmd->full_path, current_cmd->args, prompt->envp) == -1)
            handle_error("execve error");
}