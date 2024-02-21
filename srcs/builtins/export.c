/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:59:22 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/21 16:09:46 by mayeung          ###   ########.fr       */
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