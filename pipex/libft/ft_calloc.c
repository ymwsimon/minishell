/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:53:21 by mayeung           #+#    #+#             */
/*   Updated: 2023/10/16 15:48:31 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char			*t;
	size_t			i;
	unsigned int	maxsize;

	t = 0;
	maxsize = -1;
	if ((nmemb <= maxsize || size <= maxsize) && nmemb * size <= maxsize)
		t = malloc(nmemb * size);
	i = 0;
	while (t && i < (nmemb * size))
		t[i++] = 0;
	return (t);
}
