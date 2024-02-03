/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 19:16:35 by mayeung           #+#    #+#             */
/*   Updated: 2023/11/11 23:19:37 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*t;

	i = 0;
	t = 0;
	while (s && s[i])
		i++;
	t = malloc(i + 1);
	i = 0;
	while (t && s && s[i])
	{
		t[i] = s[i];
		i++;
	}
	if (t)
		t[i] = 0;
	return (t);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;

	res = 0;
	if (!s1 && s2)
		res = ft_strdup(s2);
	if (s1 && !s2)
		res = ft_strdup(s1);
	if (s1 && s2)
	{
		res = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
		if (res)
		{
			res[0] = 0;
			ft_strlcat(res, s1, ft_strlen(s1) + 1);
			ft_strlcat(res, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
		}
	}
	return (res);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (dst && dst[i] && i < size)
		i++;
	j = 0;
	while (dst && src && src[j] && i + j + 1 < size)
	{
		dst[i + j] = src[j];
		j++;
	}
	if (dst && i + j < size)
		dst[i + j] = 0;
	while (src && src[j])
		j++;
	return (i + j);
}

void	ft_strncpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (dst && src && i + 1 < size && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	if (dst && i < size)
		dst[i] = 0;
}
