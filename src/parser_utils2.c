/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:04:41 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/24 19:38:35 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**fill_args(char **args, char **lex, int lex_pos, t_envv *env)
{
	int		i;
	int		j;

	i = dbl_len(args);
	j = -1;
	while (lex[lex_pos] && !is_sep(lex[lex_pos][0]))
	{
		if (i == 0 && lex[lex_pos][0] == '/' && access(lex[lex_pos], F_OK) == 0
			&& is_inpath(lex[lex_pos], env))
			args[i] = path2cmd(lex[lex_pos]);
		else
		{
			args[i] = ft_calloc(sizeof(char), ft_strlen(lex[lex_pos]) + 1);
			if (!args[i])
				return (NULL);
			while (lex[lex_pos][++j])
				args[i][j] = lex[lex_pos][j];
			args[i][j] = '\0';
		}
		i++;
		lex_pos++;
		j = -1;
	}
	args[i] = NULL;
	return (args);
}

char	**add_arg(char **args, char **lex, t_iptrs *iptrs, t_envv *env)
{
	int	ct;

	ct = 0;
	args = fill_args(args, lex, *iptrs->i, env);
	if (ft_strchr(args[0], SQUOTE) || ft_strchr(args[0], DQUOTE))
	{
		ct = ct_quotes(args[0]);
		args[0] = rm_quotes(args[0], ct);
	}
	if (args[0][0] == '/' && access(args[0], F_OK) == 0
			&& is_inpath(args[0], env))
		args[0] = path2cmd(args[0]);
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
