/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:55:14 by mayeung           #+#    #+#             */
/*   Updated: 2023/10/16 17:08:24 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	r;
	int		t;
	int		sign;
	int		ten;

	t = n;
	ten = 1;
	sign = 1;
	if (n < 0)
	{
		write(fd, "-", 1);
		sign = -1;
	}
	while (t / 10)
	{
		ten *= 10;
		t /= 10;
	}
	while (ten)
	{
		r = n / ten * sign + '0';
		write(fd, &r, 1);
		n %= ten;
		ten /= 10;
	}
}
