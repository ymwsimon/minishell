/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:56:14 by mayeung           #+#    #+#             */
/*   Updated: 2023/10/16 15:35:02 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*t;

	i = 0;
	t = 0;
	while (s && s[i])
		i++;
	t = malloc(sizeof(char) * (i + 1));
	if (t)
	{
		i = 0;
		while (s && s[i])
		{
			t[i] = s[i];
			i++;
		}
		t[i] = 0;
	}
	return (t);
}
