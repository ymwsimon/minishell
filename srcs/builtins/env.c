/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:47:31 by mayeung           #+#    #+#             */
/*   Updated: 2024/03/06 01:22:07 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_getenv(char *str)
{
	char	*res;
	int		i;

	res = NULL;
	i = ft_search_string_arr_prefix(ft_vars()->env, str, 1);
	if (i != -1)
		res = ft_strchr(ft_vars()->env[i], '=') + 1;
	return (res);
}

char	**ft_cpy_env(char **arr)
{
	size_t	i;
	char	**new_env;

	i = ft_char_arr_size(arr);
	new_env = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (arr[i])
	{
		new_env[i] = ft_strdup(arr[i]);
		i++;
	}
	return (new_env);
}

int	ft_print_env(void)
{
	size_t	i;

	i = 0;
	while (ft_vars()->env && ft_vars()->env[i])
	{
		printf("%s\n", ft_vars()->env[i]);
		i++;
	}
	return (0);
}

int	ft_env(char **args)
{
	if (ft_char_arr_size(args) != 1)
		return (1);
	ft_print_env();
	return (0);
}
