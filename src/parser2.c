/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 20:32:13 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/10 19:23:41 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*fill_path(char *path, t_envv *env_lst, char *first_arg)
{
	char	**path_vls;
	int		i;
	char	*aux;

	i = 0;
	path_vls = get_ptharr(env_lst);
	while (path_vls[i])
	{
		aux = ft_strjoin(path_vls[i], "/");
		path = ft_strjoin(aux, first_arg);
		free(aux);
		if (access(path, F_OK) == 0)
			break ;
		else
		{
			if (path)
				free(path);
			path = NULL;
			i++;
		}
	}
	free_all(path_vls, dbl_len(path_vls));
	return (path);
}

static int	parse_executable(char **lex, t_iptrs *ip, t_cmd *s)
{
	if (access(lex[*ip->i], X_OK) == -1)
	{
		handle_error(lex[*ip->i], strerror(errno));
		(*ip->i)++;
		g_exst = 127;
		return (-1);
	}
	else
		s->full_path = ft_strdup(lex[*ip->i]);
	(*ip->i)++;
	return (0);
}
static char	*dots2path(char *ar)
{
	char	*s;
	int		i;
	char	*res;
	int		len;

	len = 0;
	i = ft_strlen(ar) - 1;
	res = ar;
	s = malloc(sizeof(char) * (MAXPATHLEN + 1));
	if (!s)
		return (NULL);
	getcwd(s, MAXPATHLEN);
	len = ft_strlen(s);
	if (i == 0 && ar[0] == '.')
		res = s;
	else if (i == 1 && ar[0] == '.' && ar[1] == '.')
	{
		while (len >= 0 && s[len] != '/')
			len--;
		res = ft_substr(s, 0, len);
		free(s);
	}
	free(ar);
	return (res);
}

static char	*upd_if_cddots(char	*ar)
{
	if (ft_strlen(ar) > 2 || ar[0] != '.' || (ft_strlen(ar) == 2
		&& ar[1] != '.'))
		return (ar);
	else
		return (dots2path(ar));
}

int	upd_node(t_cmd *s, char **lex, t_envv *env, t_iptrs *ip)
{
	if (lex[*ip->i][0] == '<' && lex[*ip->i + 1][0] == '>')
	{
		(*ip->i)++;
		return (0);
	}
	else if ((lex[*ip->i][0] == '<' && assign_infile(lex, *ip->i + 1, s) == -1)
		|| (lex[*ip->i][0] == '>' && assign_outfile(lex, *ip->i + 1, s) == -1))
	{
		g_exst = 1;
		return (-1);
	}
	else if ((lex[*ip->i][0] == '<' && lex[*ip->i + 1][0] != '>')
		|| lex[*ip->i][0] == '>')
		*ip->i += 2;
	else if (dbl_len(s->args) == 0 && lex[*ip->i][0] == '.'
		&& lex[*ip->i][1] == '/')
	{
		if (parse_executable(lex, ip, s) == -1)
			return (-1);
	}
	else
		s->args = add_arg(s->args, lex, ip, env);
	if (dbl_len(s->args) > 1 && ft_strcmp(s->args[0], "cd") == 0)
		s->args[1] = upd_if_cddots(s->args[1]);
	return (0);
}
