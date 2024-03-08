/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:29:19 by mayeung           #+#    #+#             */
/*   Updated: 2024/03/08 16:54:09 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	ft_char_arr_size(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	*ft_clear_char_arr(char **arr)
{
	size_t	i;

	i = 0;
	while (arr && arr[i])
		free(arr[i++]);
	free(arr);
	return (NULL);
}

char	*ft_free_join_str(char *str1, char *str2)
{
	char	*res;

	res = NULL;
	if (str1 && str2)
		res = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
	return (res);
}

char	*ft_create_unexpected_message(char *str)
{
	char	*res;

	if (!str)
		res = ft_strdup("minishell: syntax error near unexpected token");
	else
	{
		res = ft_strdup("minishell: syntax error near unexpected token `");
		if (ft_strncmp(str, "\n", 2))
			res = ft_free_join_str(res, ft_strdup(str));
		else
			res = ft_free_join_str(res, ft_strdup("newline"));
		res = ft_free_join_str(res, ft_strdup("'\n"));
	}
	return (res);
}
