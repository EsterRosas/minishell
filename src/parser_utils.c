/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 19:05:44 by erosas-c          #+#    #+#             */
/*   Updated: 2023/12/12 20:46:20 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*rm_quotes(int n, char *s)
{
	char	*res;
//	char	*aux;
//	int		i;

//	i = 0;
	res = ft_substr(s, n, ft_strlen(s) - (n * 2));
/* TRYING TO DELETE CONSECUTIVE QUOTES after deleting the ones in the ends
 * MAYBE this can be done before, in the lexer, I mean before the parser.
 * EVEN in trim; Need to think the order, as each quotation mark takes as its
 * corresponding closing one th first one found in the string. THINK about
 * quotations inside quotation (of different type);
 * aux = res;
	while ((aux[i] == SQUOTE && aux[i + 1] == SQUOTE) || (aux[i] == DQUOTE
			&& aux[i + 1] == DQUOTE))
		aux = ft_substr(aux, 2, ft_strlen(aux) - 2);
	res = aux;
	free(aux);*/
	free(s);
	return (res);
}

/* Delete quotation marks at the first position and last of all the strings
 * as far as they are in both places and are the same. If more than one, need to
 * be the same type (squotes or dquotes) as the ones in the innitial ends,
 * according to bash behaviour.
 */
void	del_all_quotes(char **args)
{
	int	i;
	int	l;
	int	j;

	i = 0;
	l = 0;
	j = 0;
	while (args[i])
	{
		l = ft_strlen(args[i]);
		if (l > 1 && args[i][0] == SQUOTE && args[i][l - 1] == SQUOTE)
		{
			while (args[i][j] == SQUOTE && args[i][l - 1 - j] == SQUOTE)
				j++;
			args[i] = rm_quotes(j, args[i]);
		}
		else if (l > 1 && args[i][0] == DQUOTE && args[i][l - 1] == DQUOTE)
		{
			while (args[i][j] == DQUOTE && args[i][l - 1 - j] == DQUOTE)
				j++;
			args[i] = rm_quotes(j, args[i]);
		}
		i++;
	}
}

int	assign_infile(char	*file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	//if the file doesn't exist yet, now its returning the error, but we should
	//create it instead
	if (fd == -1)
	{
		printf("Error opening file %s\n", file);
		return (-1);
	}
	else
		return (fd);
}

int	assign_outfile(char	*file)
{
	int	fd;

	fd = open(file, O_WRONLY);
	if (fd == -1)
	{
		printf("Error opening file %s\n", file);
		return (-1);
	}
	else
		return (fd);
}

void	free_cmds(char **lexed, t_cmd *cmd)
{
	int	i;
	int	cmd_n;

	i = 0;
	cmd_n = 1;
	while (i < dbl_len(lexed))
	{
		if (lexed[i][0] == '|')
			cmd_n++;
		i++;
	}
	while (cmd_n > 0)
	{
		if (cmd->full_path)
			free(cmd->full_path);
		free(&cmd[cmd_n - 1]);
		cmd_n--;
	}
}
