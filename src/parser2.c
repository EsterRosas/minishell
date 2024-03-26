/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 20:32:13 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/25 21:19:11 by erosas-c         ###   ########.fr       */
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

char	*dots2path(char *ar)
{
	char	*res;
	int		len;
	int		j;
	char	*s;

	len = 0;
	res = NULL;
	j = -1;
	s = ft_calloc(sizeof(char), (MAXPATHLEN + 1));
	if (!s)
		return (NULL);
	getcwd(s, MAXPATHLEN);
	len = ft_strlen(s);
	while (len >= 0 && s[len] != '/')
		len--;
	res = ft_calloc(sizeof(char), len);
	if (!res)
		return (NULL);
	while (++j < len)
		res[j] = s[j];
	res[j] = '\0';
	free(s);
	free(ar);
	return (res);
}

char	*dot2path(char *ar)
{
	char	*res;
	int		len;
	int		j;
	char	*s;

	len = 0;
	res = NULL;
	j = -1;
	s = ft_calloc(sizeof(char), (MAXPATHLEN + 1));
	if (!s)
		return (NULL);
	getcwd(s, MAXPATHLEN);
	len = ft_strlen(s);
	res = ft_calloc(sizeof(char), len + 1);
	if (!res)
		return (NULL);
	while (s[++j])
		res[j] = s[j];
	res[j] = '\0';
	free(s);
	free(ar);
	return (res);
}

int	upd_node(t_cmd *s, char **lex,/* t_envv *env,*/ t_iptrs *ip)
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
		*ip->i += 2;
		return (0);
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
		s->args = add_arg(s->args, lex, ip/*, env*/);
	return (0);
}
