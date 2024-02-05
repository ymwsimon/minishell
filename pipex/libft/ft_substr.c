/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:58:18 by mayeung           #+#    #+#             */
/*   Updated: 2023/12/29 16:01:37 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;
	size_t	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
		len = 0;
	if (len > slen - start)
		len = slen - start;
	res = malloc(len + 1);
	i = 0;
	while (res && i < len)
	{
		res[i] = s[start + i];
		i++;
	}
	if (res)
		res[i] = 0;
	return (res);
}
