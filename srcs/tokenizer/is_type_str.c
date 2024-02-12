/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:58:34 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/12 14:55:22 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_double_quote(char *str)
{
	return (!ft_strncmp(str, "\"", ft_strlen("\"") + 1));
}

int	ft_is_single_quote(char *str)
{
	return (!ft_strncmp(str, "'", ft_strlen("'") + 1));
}

int	ft_is_open_paren(char *str)
{
	return (!ft_strncmp(str, "(", ft_strlen("(") + 1));
}

int	ft_is_close_paren(char *str)
{
	return (!ft_strncmp(str, ")", ft_strlen(")") + 1));
}

int	ft_is_pipe(char *str)
{
	return (!ft_strncmp(str, "|", ft_strlen("|") + 1));
}
