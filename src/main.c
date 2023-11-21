/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:38:52 by erosas-c          #+#    #+#             */
/*   Updated: 2023/11/21 20:26:27 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/defines.h"
#include <fcntl.h>

int main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)argc;
	(void)envp;
	static char *line = NULL;
	loop_prompt(line);
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
