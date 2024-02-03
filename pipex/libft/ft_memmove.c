/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:54:35 by mayeung           #+#    #+#             */
/*   Updated: 2023/10/16 17:01:41 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*d;
	const char	*s;

	d = dest;
	s = src;
	if (s && d)
	{
		i = 0;
		if (s < d)
			i = n - 1;
		while (i < n)
		{
			d[i] = s[i];
			if (s > d)
				i++;
			else
				i--;
		}
	}
	return (dest);
}
