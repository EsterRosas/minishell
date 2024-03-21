/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecabanas <ecabanas@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 19:05:46 by ecabanas          #+#    #+#             */
/*   Updated: 2022/02/10 19:30:24 by ecabanas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t		i;
	const void	*ptr;

	i = 0;
	while (s[i] != '\0')
	{
		ptr = &s[i];
		write(fd, ptr, sizeof(char));
		i++;
	}
}
