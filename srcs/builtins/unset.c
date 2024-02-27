/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:22:06 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/27 18:07:57 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_remove_from_env(char *str)
{
    int     i;
    char    *to_remove;

	if (!ft_vars()->env || !ft_vars()->env[0])
		return (0);
    i = ft_search_string_arr_prefix(ft_vars()->env, str, 1);
	printf("idx in env: %s %d\n", str, i);
	if (i == -1)
		return (0);
    to_remove = ft_vars()->env[i];
    while (ft_vars()->env[i])
    {
		ft_vars()->env[i] = ft_vars()->env[i + 1];
		i++;
	}
	free(to_remove);
	return (0);
}

int ft_unset(char **args)
{
	size_t	i;
	int		status;

	i = 1;
	status = 0;
	if (!args || !args[0] || !ft_vars()->env[0])
		return (0);
	while (args[i])
	{
		if (ft_search_string_arr_prefix(ft_vars()->env, args[i], 1) != -1)
			status |= ft_remove_from_env(args[i]);
		i++;
	}
	return (status);
}