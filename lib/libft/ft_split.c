/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecabanas <ecabanas@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 12:12:56 by ecabanas          #+#    #+#             */
/*   Updated: 2022/02/20 12:30:33 by ecabanas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**free_all(char	**res, int n)
{
	while (n >= 0)
	{
		free(res[n]);
		n--;
	}
	free(res);
	return (0);
}

char	*find_ptr(char const *ptr, char c)
{
	while (*ptr == c && *ptr)
		ptr++;
	return ((char *)ptr);
}

static int	word_len(char const *ptr, char c)
{
	size_t	i;

	i = 0;
	while (ptr[i] != '\0' && ptr[i] != c)
		i++;
	return (i);
}

static int	word_count(char const *s, char c)
{
	int	str_count;
	int	i;

	str_count = 0;
	i = 0;
	if (*s == '\0')
		return (0);
	while (s[i])
	{
		if (s[i] != c && s[i + 1] == c)
			str_count++;
		i++;
	}
	if (s[i - 1] != c)
		str_count++;
	if (c == 0)
		str_count--;
	return (str_count);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	words;
	size_t	i;
	char	*ptr;

	if (!s)
		return (0);
	words = word_count (s, c);
	res = malloc(sizeof(char *) * (words + 1));
	if (!res)
		return (0);
	i = 0;
	while (i < words)
	{
		ptr = find_ptr(s, c);
		res[i] = ft_substr(ptr, 0, word_len(ptr, c));
		if (res[i] == 0)
			return (free_all(res, i));
		i++;
		s = s + (ptr - s) + word_len(ptr, c);
	}	
	res[i] = NULL;
	return (res);
}
