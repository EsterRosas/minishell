/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecabanas <ecabanas@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:26:28 by ecabanas          #+#    #+#             */
/*   Updated: 2022/03/01 17:48:03 by ecabanas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = (char *) s;
	while (ptr[i])
	{
		if (ptr[i] == (char) c)
			return (&ptr[i]);
		i++;
	}
	if (ptr[i] == (char)c)
		return (&ptr[i]);
	return (0);
}
