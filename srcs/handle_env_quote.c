/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:33:30 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/20 17:26:43 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_convert_env_var(char *str, size_t i, size_t *j)
{
	char	*res;
	char	*tmp;

	*j = i;
	while (str[*j] && ft_isalnum(str[*j]))
		(*j)++;
	tmp = ft_substr(str, i, (*j) - i);
	if (!tmp)
		return (NULL);
	res = getenv(tmp);
	free(tmp);
	if (!res)
		res = ft_strdup("");
	return (ft_strdup(res));
}

char	*ft_convert_single_quote(char *str, size_t i, size_t *j)
{
	char	*res;

	*j = i;
	while (str[*j] && str[*j] != '\'')
		(*j)++;
	res = ft_substr(str, i, (*j) - i);
	(*j)++;
	return (res);
}

char	*ft_convert_double_quote(char *str, size_t i, size_t *j, int is_deli)
{
	char	*res;

	res = ft_strdup("");
	if (!res)
		return (NULL);
	while (str[i] && str[i] != '"')
	{
		*j = i;
		while (str[*j] && (str[*j] != '$' || is_deli) && str[*j] != '"')
			(*j)++;
		res = ft_free_join_str(res, ft_substr(str, i, (*j) - i));
		if (str[*j] == '$')
			res = ft_free_join_str(res, ft_convert_env_var(str, (*j) + 1, j));
		i = *j;
	}
	(*j)++;
	return (res);
}

char	*ft_string_resolve(char *str, int is_deli)
{
	char	*res;
	size_t	i;
	size_t	j;

	i = 0;
	res = ft_strdup("");
	while (str[i])
	{
		j = i;
		if (str[i] == '"')
			res = ft_free_join_str(res,
					ft_convert_double_quote(str, ++i, &j, is_deli));
		else if (str[i] == '\'')
			res = ft_free_join_str(res, ft_convert_single_quote(str, ++i, &j));
		else if (str[i] == '$' && !is_deli)
			res = ft_free_join_str(res, ft_convert_env_var(str, ++i, &j));
		else
		{
			while (str[j] && str[j] != '"' && str[j] != '\'')
				j++;
			res = ft_free_join_str(res, ft_substr(str, i, j - i));
		}
		i = j;
	}
	return (free(str), res);
}