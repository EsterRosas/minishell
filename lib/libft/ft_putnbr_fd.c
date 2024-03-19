/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecabanas <ecabanas@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 19:48:30 by ecabanas          #+#    #+#             */
/*   Updated: 2022/02/13 11:56:04 by ecabanas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	lnb;
	long int	i;

	lnb = n;
	if (lnb == 0)
		ft_putchar_fd('0', fd);
	else if (lnb < 0)
	{
		lnb *= -1;
		ft_putchar_fd('-', fd);
	}
	i = 1;
	while (lnb / i != 0)
		i *= 10;
	while (i != 1)
	{
		i /= 10;
		ft_putchar_fd((lnb % (10 * i) - lnb % i) / i + '0', fd);
	}
}
