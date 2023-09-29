/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecabanas <ecabanas@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:59:01 by ecabanas          #+#    #+#             */
/*   Updated: 2022/02/20 11:45:02 by ecabanas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	size;
	size_t	new_size;

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
	ft_strlcpy (ptr, (s + start), (new_size + 1));
	return (ptr);
}
