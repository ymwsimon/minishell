/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:53:21 by mayeung           #+#    #+#             */
/*   Updated: 2023/12/28 12:57:09 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*t;
	size_t	i;
	size_t	total;

	total = nmemb * size;
	if (size && total / size != nmemb)
		return (NULL);
	t = malloc(total);
	i = 0;
	while (t && i < total)
		t[i++] = 0;
	return (t);
}
