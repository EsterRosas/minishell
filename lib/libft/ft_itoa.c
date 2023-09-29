/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecabanas <ecabanas@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:02:50 by ecabanas          #+#    #+#             */
/*   Updated: 2022/03/01 18:46:56 by ecabanas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	counter(int n)
{
	int	i;

	if (n == 0)
		return (1);
	i = 0;
	if (n < 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	loop(int n, int size, int i, char *ptr)
{
	while (size-- > i)
	{
		if (n < 0)
		{
			ptr[size] = '0' + n % 10 * (-1);
			n /= 10;
		}
		else
		{
			ptr[size] = (n % 10) + '0';
			n /= 10;
		}
	}
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		size;
	int		i;

	size = counter(n);
	ptr = (char *) malloc(sizeof(char) * size + 1);
	if (!ptr)
		return (0);
	ptr[size] = '\0';
	if (n < 0)
	{
		ptr[0] = '-';
		i = 1;
	}
	else
		i = 0;
	loop(n, size, i, ptr);
	return (ptr);
}
