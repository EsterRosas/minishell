/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:47:13 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/16 20:33:49 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	even_quotes(char *p, char c)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (p[i])
	{
		if (p[i] && p[i] == c)
			num++;
		i++;
	}
	if (num == 1 || num % 2 != 0)
		return (1);
	return (0);
}

static int	check_quotes(char **lex)
{
	int	i;

	i = 0;
	while (lex[i])
	{
		if (ft_strchr(lex[i], SQUOTE) && even_quotes(lex[i], SQUOTE))
		{
			handle_error_syn("syntax error near unexpected token", lex[i]);
			return (1);
		}
		else if (ft_strchr(lex[i], DQUOTE) && even_quotes(lex[i], DQUOTE))
		{
			handle_error_syn("syntax error near unexpected token", lex[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_more(char **lex)
{
	int	i;

	i = -1;
	while (lex[++i] && lex[i + 1])
	{
		if (lex[i + 1] && (lex[i][0] == '|' || lex[i][0] == '>')
			&& lex[i + 1][0] == '|')
		{
			only_msg_err("syntax error near unexpected token `|'");
			break ;
		}
		else if (lex[i + 1] && (lex[i][0] == '>' && lex[i + 1][0] == '<'))
		{
			only_msg_err("syntax error near unexpected token `<'");
			break ;
		}
	}
	if (i + 1 != dbl_len(lex))
		return (1);
	return (0);
}

int	check_syntax(char **lex)
{
	if (check_quotes(lex) == 1)
	{
		g_exst = 258;
		return (1);
	}
	if (check_more(lex) == 1)
	{
		g_exst = 258;
		return (1);
	}
	if (lex[dbl_len(lex) - 1][0] == '>' || lex[dbl_len(lex) - 1][0] == '<')
	{
		only_msg_err("syntax error near unexpected token `newline'");
		g_exst = 258;
		return (1);
	}
	else if ((lex[0][0] == '|' || lex[dbl_len(lex) - 1][0] == '|')
		|| (lex[0][0] == '<' && lex[1][0] && lex[1][0] == '|'))
	{
		only_msg_err("syntax error near unexpected token `|'");
		g_exst = 258;
		return (1);
	}
	return (0);
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
