/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:53:12 by mayeung           #+#    #+#             */
/*   Updated: 2023/10/29 12:06:38 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_isspace(char c)
{
	if (c == ' ' || c == '\n' || c == '\r' || \
		c == '\t' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	res;

	res = 0;
	sign = 1;
	while (nptr && ft_isspace(*nptr))
		nptr++;
	if (nptr && *nptr == '-')
		sign = -1;
	if (nptr && (*nptr == '+' || *nptr == '-'))
		nptr++;
	while (nptr && *nptr >= '0' && *nptr <= '9')
	{
		res *= 10;
		res += *nptr - '0';
		nptr++;
	}
	return (res * sign);
}
