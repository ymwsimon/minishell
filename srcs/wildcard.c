/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 11:05:05 by mayeung           #+#    #+#             */
/*   Updated: 2024/03/12 13:03:23 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_resolve_env_var_only(char **res, char *str)
{
	size_t	i;
	size_t	j;

	if (!str || !res)
		return (INVALID_POINTER);
	*res = ft_strdup("");
	i = 0;
	while (str[i])
	{
		j = i;
		if (str[i] == '$')
			ft_free_join_str(*res, ft_convert_env_var(str, i, &j));
		else
		{
			while (str[i] && str[i] != '$')
		}
	}
	return (EXE_SUCCESS);
}

int	ft_arg_to_linkedlist(t_list **res, char *arg)
{
	size_t	i;
	size_t	j;
	DIR		*dir;

	*res = NULL;
	i = 0;
	while (arg && arg[i])
	{
		j = i;
		i = j;
	}
	retrun (EXE_SUCCESS);
}
