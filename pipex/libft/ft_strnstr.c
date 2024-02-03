/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:57:55 by mayeung           #+#    #+#             */
/*   Updated: 2023/10/16 17:22:54 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *small, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	ls;

	if (!small[0])
		return ((char *)big);
	ls = 0;
	while (small[ls])
		ls++;
	i = 0;
	while ((i + ls) <= len && big[i])
	{
		j = 0;
		while (big[i + j] && small[j] && small[j] == big[i + j])
			j++;
		if (!small[j])
			return ((char *)&big[i]);
		i++;
	}
	return (0);
}
