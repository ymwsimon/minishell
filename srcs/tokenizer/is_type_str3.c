/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type_str3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:01:27 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/12 14:55:30 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_or(char *str)
{
	return (!ft_strncmp(str, "||", ft_strlen("||") + 1));
}

int	ft_is_redir(char *str)
{
	return (ft_is_here_doc(str)
		|| ft_is_input(str)
		|| ft_is_output(str)
		|| ft_is_append(str));
}
