/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:56:20 by mayeung           #+#    #+#             */
/*   Updated: 2023/12/28 13:23:23 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < size && dst && dst[i])
		i++;
	j = 0;
	while (i + j + 1 < size && dst && src && src[j])
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i + j < size && dst && src)
		dst[i + j] = 0;
	while (src && src[j])
		j++;
	return (i + j);
}
