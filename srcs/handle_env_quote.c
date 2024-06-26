/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:33:30 by mayeung           #+#    #+#             */
/*   Updated: 2024/03/09 14:29:07 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_convert_env_var(char *str, size_t i, size_t *j)
{
	char	*res;
	char	*tmp;

	*j = i;
	if (str && str[i] == '?')
		return ((*j)++, ft_itoa(ft_vars()->last_exe_res));
	while (str[*j] && (ft_isalnum(str[*j]) || str[*j] == '_'))
		(*j)++;
	if (*j == i)
		return (ft_strdup("$"));
	tmp = ft_substr(str, i, (*j) - i);
	if (!tmp)
		return (NULL);
	res = ft_getenv(tmp);
	free(tmp);
	if (!res)
		return (ft_strdup(""));
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

char	*ft_con_doub_quo(char *str, size_t i, size_t *j, int is_deli)
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
	while (res && str[i])
	{
		j = i;
		if (str[i] == '"')
			res = ft_free_join_str(res, ft_con_doub_quo(str, ++i, &j, is_deli));
		else if (str[i] == '\'')
			res = ft_free_join_str(res, ft_convert_single_quote(str, ++i, &j));
		else if (str[i] == '$' && !is_deli)
			res = ft_free_join_str(res, ft_convert_env_var(str, ++i, &j));
		else
		{
			while (str[j] && !ft_strchr("'\"", str[j])
				&& (str[j] != '$' || is_deli))
				j++;
			res = ft_free_join_str(res, ft_substr(str, i, j - i));
		}
		i = j;
	}
	return (free(str), res);
}
