/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:04:41 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/04 18:10:43 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**add_arg(char **args, char **lex, int *i, int *len)
{
	args = fill_args(args, lex, *i);
	*i = *i + dbl_len(args) - *len;
	*len = dbl_len(args);
	return (args);
}

int	all_args_ropt(char **ar)
{
	int	i;

	i = 0;
	while (ar[++i])
	{
		if (ar[i][0] != '-')
			return (0);
	}
	return (0);
}

int	stop_case_cat(t_cmd *s, char *l)
{
	if (s->args[0])
	{
		if (ft_strcmp(s->args[0], "cat") == 0)
		{
			if (s->args[1] && !all_args_ropt(s->args))
				return (1);
			else if (s->infile != 0 && l[0] != '-')
				return (1);
		}
	}
	return (0);
}
