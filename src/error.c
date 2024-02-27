/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:05:42 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/26 12:54:13 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_error(const char *message)
{
	perror(message);
/*  const char *error_message = strerror(errno);
    printf("%s: %s\n", message, error_message); */
	exit(EXIT_FAILURE);
}

void	ft_exporterror(char *cmd, char *s, char *msg)
{
	printf("minishell: %s: `%s': %s\n", cmd, s, msg);
}


