/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:47:31 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/26 21:46:14 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cpy_env(char ***arr)
{
	size_t	i;
	char	**new_env;

	i = ft_char_arr_size(*arr);
	new_env = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while ((*arr)[i])
	{
		new_env[i] = ft_strdup((*arr)[i]);
		i++;
	}
	*arr = new_env;
	return (0);
}

int	ft_print_env(void)
{
	size_t	i;

	i = 0;
	while (__environ && __environ[i])
	{
		printf("%s\n", __environ[i]);
		i++;
	}
	return (0);
}

int ft_env(char **args)
{
	if (ft_char_arr_size(args) != 1)
		return (1);//print error
	ft_print_env();
	return (0);
}
