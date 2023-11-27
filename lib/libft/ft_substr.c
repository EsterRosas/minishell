/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecabanas <ecabanas@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:59:01 by ecabanas          #+#    #+#             */
/*   Updated: 2023/11/27 20:54:08 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	size;
	size_t	new_size;
	size_t	i;

	if (!s)
		return (0);
	size = ft_strlen(s);
	if (start >= size)
		return (ft_strdup(""));
	new_size = size - start;
	if (new_size > len)
		new_size = len;
	ptr = (char *) malloc(sizeof(char) * (new_size + 1));
	if (!ptr)
		return (0);
	//ft_strlcpy (ptr, (s + start), (new_size + 1));
	i = 0;
	while (i < new_size)
	{
		ptr[i] = s[start];
		i++;
		start++;
	}
	ptr[i] = '\0';
	return (ptr);
}
