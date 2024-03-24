/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 16:31:36 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/24 17:49:43 by erosas-c         ###   ########.fr       */
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
