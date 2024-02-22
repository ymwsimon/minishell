/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 20:18:39 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/20 21:08:03 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_char_arr(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
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

int	ft_export(char **args)
{
	size_t	i;
	int		j;

	if (args && ft_char_arr_size(args) == 1)
		ft_print_char_arr(__environ);
	else if (args)
	{
		i = 0;
		while (args[i])
		{
			j = 0;
			while (args[i][j] && args[i][j] != '=')
				j++;
			j = ft_search_char_arr_prefix(__environ, args[i], j + 1);
			if (j >= 0)
				;//ft_update_env(__environ, args[i], j);
			else
				{;}//ft_append_env(__environ, args[i]);
			i++;
		}
	}
	return (0);
}
