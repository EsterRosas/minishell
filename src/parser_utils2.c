/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:04:41 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/05 19:46:07 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*path2cmd(char *arg)
{
	int		i;

	i = ft_strlen(arg) - 1;
	while (i >= 0 && arg[i] != '/')
		i--;
	return (ft_substr(arg, i + 1, ft_strlen(arg) - 1));
}

int	**get_iptrarr(int i, int len)
{
	int	**res;

	res = (int **)malloc(sizeof(int) * 2);
	if (!res[0])
		return (NULL);
	res[0] = &i;
	res[1] = &len;
	return (res);
}

char	**add_arg(char **args, char **lex, t_iptrs *iptrs, t_envv *env)
{
	args = fill_args(args, lex, *iptrs->i, env);
	*iptrs->i = *iptrs->i + dbl_len(args) - *iptrs->len;
	*iptrs->len = dbl_len(args);
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
