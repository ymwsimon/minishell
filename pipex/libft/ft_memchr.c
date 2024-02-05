/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:54:24 by mayeung           #+#    #+#             */
/*   Updated: 2023/12/28 13:04:22 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*ss;

	i = 0;
	ss = s;
	while (i < n)
	{
		if (ss[i] == (unsigned char)c)
			return ((void *)ss + i);
		i++;
	}
	return (0);
}
