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

char	**fill_args(char **args, char **lex)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (lex[i] && !is_sep(lex[i][0]))
	{
		args[i] = malloc(sizeof(char) * ft_strlen(lex[i]) + 1);
		if (!args[i])
			return (NULL);
		while (lex[i][j])
		{
			args[i][j] = lex[i][j];
			j++;
		}
		args[i][j] = '\0';
		i++;
		j = 0;
	}
	args[i] = NULL;
	return (args);
}

t_cmd	fill_node(t_cmd s, char **lex)
{
	int	i;

	i = 0;
	while (lex[i] && lex[i][0] != '|')
	{
		if (ft_strlen(lex[i]) == 1 && (lex[i][0] == '<' || lex[i][0] == '>'))
		{
			if (lex[i][0] == '<')
				s.infile = assign_infile(lex[++i]);
			else
				s.outfile = assign_outfile(lex[++i]);
		}
		else
		{
			s.args = fill_args(s.args, lex);
			i = i + dbl_len(s.args);
		}
		i++;
	}
	return (s);
}

t_cmd	*parse_lexed(char **lex)
{
	int		i;
	t_cmd	*res;
	int		cmd_n;

	i = -1;
	cmd_n = 1;
	while (++i < dbl_len(lex))
	{
		if (lex[i][0] == '|')
			cmd_n++;
	}
	res = malloc(sizeof(t_cmd) * cmd_n);
	if (!res)
		return (NULL);
	i = -1;
	while (++i < cmd_n)
	{
		res[i].args = malloc(sizeof(char *) * dbl_len(lex) + 1);
		res[i].full_path = NULL;
		res[i].infile = STDIN_FILENO;
		res[i].outfile = STDOUT_FILENO;
		res[i] = fill_node(res[i], lex);
	}
	return (res);
}
