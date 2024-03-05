/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:22:10 by damendez          #+#    #+#             */
/*   Updated: 2024/03/05 17:50:39 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// int is_directory(char *path)
// {

// }

int executable_path(char *path)
{
    if (access(path, X_OK) == -1)
        return (1);
    return (0);
}