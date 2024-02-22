/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 20:18:39 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/22 00:58:46 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_print_env(void)
{
	size_t	i;

	i = 0;
	while (__environ[i])
	{
		printf("%s\n", __environ[i]);
		i++;
	}
	return (0);
}

int	ft_search_char_arr_prefix(char **arr, char *str, size_t len)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		if (!ft_strncmp(arr[i], str, len))
			return (i);
	}
	return (-1);
}

int ft_export(char **args)
{
	size_t	i;

	if (!args)
		return (1);
    if (ft_char_arr_size(args) == 1)
		return (ft_print_env());
	i = 1;
	while (args[i])
	{
		if (ft_valid_export_args(args[i]))
		{}
		else
			return (1);
		i++;
	}	
    return (0);
}
