/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 20:32:13 by erosas-c          #+#    #+#             */
/*   Updated: 2023/12/07 21:03:26 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*t_cmd	*add_arg(char *s)
{
	t_cmd	*cmd;



	return (cmd);
}*/

void	parse_lexed(char **lex)
{
	int			i;
//	t_prompt	*res;
	int			cmd_n;

	i = 0;
	cmd_n = 1;
	while (i < dbl_len(lex))
	{
		if (lex[i][0] == '|')
			cmd_n++;
		i++;
	}
	printf("cmd_n: %i\n", cmd_n);
	//return (res);
}
