/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 20:32:13 by erosas-c          #+#    #+#             */
/*   Updated: 2023/12/12 20:33:40 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	cmdlst_addback(t_cmd *cmdlst, t_cmd *new)
{
	if (cmdlst == 0)
		cmdlst = new;
	else
	{
		if (!cmdlst)
			return;
		while (cmdlst->next)
			cmdlst = cmdlst->next;
	}
	cmdlst->next = new;
}
void	fill_cmdlst(char **lex, t_envv *env_lst, t_cmd *cmdlst, int cmd_n)
{
	int		i;
	t_cmd	*new;

	i = 0;
	while (++i < cmd_n)
	{
		while (*lex && *lex[0] != '|')
			lex++;
		if (*lex && *lex[0] == '|')
		{
			lex++;
			new = get_cmd(lex, env_lst);
			cmdlst_addback(cmdlst, new);
		}
	}
}
