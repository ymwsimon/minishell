/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:56:14 by mayeung           #+#    #+#             */
/*   Updated: 2023/12/29 01:13:47 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*t;

	if (!s)
		return (NULL);
	t = malloc(sizeof(char) * (ft_strlen(s) + 1));
	i = 0;
	while (t && s[i])
	{
		t[i] = s[i];
		i++;
	}
	if (t)
		t[i] = 0;
	return (t);
}
