/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecabanas <ecabanas@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 18:37:22 by ecabanas          #+#    #+#             */
/*   Updated: 2022/02/01 17:34:09 by ecabanas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *s1, const void *s2, size_t n)
{
	unsigned char		*us1;
	const unsigned char	*us2;

	us1 = (unsigned char *) s1;
	us2 = (const unsigned char *) s2;
	if (s1 < s2)
		return (ft_memcpy(s1, s2, n));
	if (!n || (s1 == s2))
		return (s1);
	while (n--)
		us1[n] = us2[n];
	return (s1);
}
