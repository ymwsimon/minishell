/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:45:39 by mayeung           #+#    #+#             */
/*   Updated: 2024/03/06 18:34:27 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_vars	*ft_vars(void)
{
	static t_vars	v = (t_vars){NULL, NULL, NULL, 0, 0};

	return (&v);
}

int	ft_event(void)
{
	return (0);
}
