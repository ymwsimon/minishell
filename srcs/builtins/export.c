/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 20:18:39 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/24 18:39:08 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_search_char_arr_prefix(char **arr, char *str, int full_len)
{
	int	i;
	int	len;

	len = 0;
	while (str && str[len] && str[len] != '=')
		len++;
	i = 0;
	while (arr && arr[i])
	{
		if (full_len)
		{
			len = 0;
			while (arr[i][len] && arr[i][len] != '=')
				len++;
		}
		if (!ft_strncmp(arr[i], str, len))
			return (i);
		i++;
	}
	return (-1);
}

int	ft_valid_export_args(char *arg)
{
	size_t	i;

	i = 0;
	if (!arg || !ft_isalpha(arg[0]))
		return (0);
	while (arg[i] && ft_isalnum(arg[i]))
		i++;
	if (arg[i] != '=' || (arg[i] == '=' && !arg[i + 1]))
		return (0);
	return (1);
}

int	ft_update_env(char *str)
{
	int		i;
	char	*old_value;

	i = ft_search_char_arr_prefix(__environ, str, 0);
	old_value = __environ[i];
	__environ[i] = ft_strdup(str);
	if (!__environ[i])
		return (1);
	old_value+=0;
	//free(old_value);
	return (0);
}

int	ft_add_to_env(char *str)
{
	char	**old_env;
	size_t	i;

	i = ft_char_arr_size(__environ);
	old_env = __environ;
	__environ = ft_calloc(i + 2, sizeof(char *));
	if (!__environ)
		return (1);
	i = 0;
	while (old_env[i])
	{
		__environ[i] = old_env[i];
		i++;
	}
	__environ[i] = ft_strdup(str);
	free(old_env);
	if (!__environ[i])
		return (1);
	return (0);
}

int	ft_export(char **args)
{
	size_t	i;
	int		status;

	if (!args)
		return (1);
	if (ft_char_arr_size(args) == 1)
		return (ft_print_env());
	i = 1;
	status = 0;
	while (args[i])
	{
		if (ft_valid_export_args(args[i]))
		{
			printf("the idx:%d\n", ft_search_char_arr_prefix(__environ, args[i], 0));
			if (ft_search_char_arr_prefix(__environ, args[i], 0) != -1)
				status = ft_update_env(args[i]);
			else
				status = ft_add_to_env(args[i]);
		}
		else
			status = 1;
		i++;
	}	
	return (status);
}
