/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:22:06 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/24 18:43:00 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_remove_from_env(char *str)
{
    int     i;
    char    *to_remove;

	if (!__environ || !__environ[0])
		return (0);
    i = ft_search_char_arr_prefix(__environ, str, 1);
	if (i == -1)
		return (0);
    to_remove = __environ[i];
    while (__environ[i])
    {
		__environ[i] = __environ[i + 1];
		i++;
	}
	to_remove+=0;
	//free(to_remove);
	return (0);
}

int ft_unset(char **args)
{
	size_t	i;
	int		status;

	i = 1;
	status = 0;
	if (!args || !args[0] || !__environ[0])
		return (0);
	while (args[i])
	{
		if (ft_search_char_arr_prefix(__environ, args[i], 1) != -1)
			status |= ft_remove_from_env(args[i]);
		i++;
	}
	return (status);
}