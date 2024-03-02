/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:05:42 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/01 18:17:16 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_error(char *cmd, char *message)
{
//	printf("minishell: %s: %s\n", message, strerror(errno));
	write(2, "minishell: ", 11);
   	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
//	exit(EXIT_FAILURE);
}

void	handle_error_opt(char *cmd, char *option, char *message)
{
//	printf("minishell: %s: %s\n", message, strerror(errno));
	write(2, "minishell: ", 11);
   	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
 	write(2, option, ft_strlen(option));
	write(2, ": ", 2);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
//	exit(EXIT_FAILURE);
}


void	ft_exporterror(char *cmd, char *s, char *msg)
{
//	printf("minishell: %s: `%s': %s\n", cmd, s, msg);
	write(2, "minishell: ", 12);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": `", 3);
 	write(2, s, ft_strlen(s));
	write(2, "': ", 3);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}
