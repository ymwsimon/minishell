/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:58:00 by mayeung           #+#    #+#             */
/*   Updated: 2023/10/16 17:24:18 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*h;

	h = (char *)s;
	if (h)
	{
		while (*h)
			h++;
		if (!c)
			return (h);
		while (h >= s)
		{
			if (*h == (char)c)
				return (h);
			h--;
		}
	}
	return (0);
}
