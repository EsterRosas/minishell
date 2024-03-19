/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecabanas <ecabanas@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 10:14:07 by ecabanas          #+#    #+#             */
/*   Updated: 2022/03/01 18:15:25 by ecabanas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	i = 0;
	if (!*needle || !ft_strlen(needle))
		return ((char *) haystack);
	if (!*haystack || ft_strlen(needle) > len)
		return (0);
	while (i < len)
	{
		if (ft_strncmp((char *) &haystack[i], needle, ft_strlen(needle)) == 0)
		{
			if (i + ft_strlen(needle) > len)
				return (0);
			return ((char *) &haystack[i]);
		}
		i++;
	}
	return (0);
}
