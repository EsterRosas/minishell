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
	
	res = ft_substr(s, n, ft_strlen(s) - (n * 2));
 	free(s);
	return (res);
}

/* Delete quotation marks at the first position and last of all the strings
 * as far as they are in both places and are the same. If more than one, need to
 * be the same type (squotes or dquotes) as the ones in the initial ends,
 * according to bash behaviour.
 */
void	del_end_quotes(char **args)
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

char	*rm_midquot(char *s, int n)
{
	char	*res;
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	res = malloc(sizeof(char) * ft_strlen(s) - n + 1);
	if (!res)
		return (NULL);
	while (s[i])
	{
		while (s[i] && s[i] != SQUOTE && s[i] != DQUOTE)
		{
			res[j] = s[i];
			i++;
			j++;
		}
		if (s[i] && (s[i] == DQUOTE || s[i] == SQUOTE))
		{
			c = s[i];
			i++;
			while (s[i] && s[i] != c)
			{
				res[j] = s[i];
				i++;
				j++;
			}
			if (s[i] && s[i] == c)
				i++;
		}
	}
	res[j] = '\0';
	free(s);
	return (res);
}

int	ct_quotes(char *p)
{
	int		i;
	int		res;
	char	c;

	i = 0;
	res = 0;
	while (p[i])
	{
		while (p[i] && p[i] != SQUOTE && p[i] != DQUOTE)
			i++;
		if (p[i] && (p[i] == DQUOTE || p[i] == SQUOTE))
		{
			c = p[i];
			res += 2;
			i++;
			while (p[i] && p[i] != c)
				i++;
			if (p[i] && p[i] == c)
				i++;
		}
	}	
	return (res);
}

/* IN PROGRESS. Once done, maybe it can also include the movements needed for del_end_quotes
 */
void	del_mid_quotes(char **s)
{
	int	i;
	int	ct;

	i = 0;
	ct = 0;
	while (s[i])
	{
		if (ft_strchr(s[i], SQUOTE) || ft_strchr(s[i], DQUOTE))
		{
			ct = ct_quotes(s[i]);
			s[i] = rm_midquot(s[i], ct);
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
