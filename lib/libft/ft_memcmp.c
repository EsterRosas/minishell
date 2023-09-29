/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecabanas <ecabanas@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 10:02:25 by ecabanas          #+#    #+#             */
/*   Updated: 2022/01/30 11:56:25 by ecabanas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*p1;
	unsigned char	*p2;
	size_t			i;

	p1 = (unsigned char *) s1;
	p2 = (unsigned char *) s2;
	if (!n)
		return (0);
	i = 0;
	while (n != 0)
	{
		if (p1[i] != p2[i])
			return ((unsigned char) p1[i] - (unsigned char) p2[i]);
		i++;
		n--;
	}
	return (0);
}
