/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:58:00 by mayeung           #+#    #+#             */
/*   Updated: 2023/12/29 15:58:41 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*h;

	h = (char *)s;
	while (h && *h)
		h++;
	while (h && h >= s)
	{
		if (*h == (char)c)
			return (h);
		h--;
	}
	return (NULL);
}
