/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:54:35 by mayeung           #+#    #+#             */
/*   Updated: 2023/12/29 15:52:19 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	d = dest;
	s = src;
	i = 0;
	if (s < d)
		i = n - 1;
	while (s && d && i < n)
	{
		d[i] = s[i];
		if (s > d)
			i++;
		else
			i--;
	}
	return (dest);
}
