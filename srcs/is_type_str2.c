/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type_str2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:59:29 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/11 18:04:31 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_here_doc(char *str)
{
	return (!ft_strncmp(str, "<<", ft_strlen("<<") + 1));
}

int	ft_is_input(char *str)
{
	return (!ft_strncmp(str, "<", ft_strlen("<") + 1));
}

int	ft_is_output(char *str)
{
	return (!ft_strncmp(str, ">", ft_strlen(">") + 1));
}

int	ft_is_append(char *str)
{
	return (!ft_strncmp(str, ">>", ft_strlen(">>") + 1));
}

int	ft_is_and(char *str)
{
	return (!ft_strncmp(str, "&&", ft_strlen("&&") + 1));
}
