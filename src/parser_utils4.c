/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 20:30:19 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/24 18:40:52 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*del_leaddol(char *s)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = -1;
	res = ft_calloc(sizeof(char), ft_strlen(s));
	if (!res)
		return (NULL);
	while (s[++i])
		res[++j] = s[i];
	res[j] = '\0';
	free(s);
	return (res);
}

t_cmd	*args_leaddol_quotes(t_cmd *cmd)
{
	t_cmd	*aux;
	int		i;

	i = 0;
	aux = cmd;
	while (aux)
	{
		if (aux->args && aux->args[0])
		{
			while (cmd->args[i])
			{
				if (ft_strlen(cmd->args[i]) > 1 && cmd->args[i][0] == '$'
					&& (cmd->args[i][1] == SQUOTE || cmd->args[i][1] == DQUOTE))
					cmd->args[i] = del_leaddol(cmd->args[i]);
				i++;
			}
			del_quotes(aux->args, 1);
		}
		aux = aux->next;
	}
	return (cmd);
}

int	path_unset_nobuilt(t_cmd *cmd, t_envv *env)
{
	t_cmd	*aux;

	if (!path_unset(env, ""))
		return (0);
	else if (cmd)
	{
		aux = cmd;
		while (aux)
		{
			if (aux->args && aux->args[0] && !is_builtin(aux->args[0]))
			{
				handle_error(aux->args[0], "No such file or directory");
				g_exst = 127;
				return (1);
			}
			aux = aux->next;
		}
	}
	return (0);
}

void	redo_path(t_cmd *cmd, t_envv *env)
{
	t_cmd	*aux;

	aux = cmd;
	while (aux)
	{
		if (!aux->full_path && aux->args && aux->args[0]
			&& aux->args[0][0] != '/' && !is_builtin(aux->args[0])
			&& ft_strcmp(aux->args[0], "") != 0)
			aux->full_path = fill_path(aux->full_path, env, aux->args[0]);
		aux = aux->next;
	}
}
int		in_savedpath(char *s, char **path)
{
	int		i;
	char	*folder;

	i = ft_strlen(s) - 1;
	while (i >= 0 && s[i] != '/')
		i--;
	folder = ft_substr(s, 0, i);
	i = -1;
	while (path[++i])
	{
		if (ft_strcmp(path[i], folder) == 0)
		{
			free(folder);
			return (1);
		}
	}
	free(folder);
	return (0);
}