/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:57:55 by mayeung           #+#    #+#             */
/*   Updated: 2023/12/29 15:32:28 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	little_len;

	little_len = 0;
	while (little && little[little_len])
		little_len++;
	if (little && !little_len)
		return ((char *)big);
	while (little && big && little_len <= len && *big)
	{
		i = 0;
		while (big[i] && little[i] && little[i] == big[i])
			i++;
		if (!little[i])
			return ((char *)big);
		len--;
		big++;
	}
	return (NULL);
}
