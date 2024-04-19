/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 16:31:36 by erosas-c          #+#    #+#             */
/*   Updated: 2024/04/01 15:43:46 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*upd_auxval(void)
{
	char	*res;

	res = ft_calloc(sizeof(char), MAXPATHLEN + 1);
	if (!res)
		return (NULL);
	getcwd(res, MAXPATHLEN);
	return (res);
}

int	do_cdonly(t_envv *env, char *oldpwd_current)
{
	if (cd_only(env) == 1)
	{
		free(oldpwd_current);
		return (1);
	}
	else
		upd_pwds(env, oldpwd_current);
	return (0);
}
