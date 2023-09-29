/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecabanas <ecabanas@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 19:42:17 by ecabanas          #+#    #+#             */
/*   Updated: 2022/03/01 18:53:03 by ecabanas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		size;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	size = 0;
	ptr = (char *) malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!s1 || !s2 || !ptr)
		return (0);
	while (i < ft_strlen(s1))
		ptr[size++] = s1[i++];
	while (j < ft_strlen(s2))
		ptr[size++] = s2[j++];
	ptr[size++] = '\0';
	return ((char *) ptr);
}
