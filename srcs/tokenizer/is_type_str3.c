/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type_str3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:01:27 by mayeung           #+#    #+#             */
/*   Updated: 2024/03/07 15:48:50 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_or(char *str)
{
	return (!ft_strncmp(str, "||", ft_strlen("||") + 1));
}

int	ft_is_newline(char *str)
{
	return (!ft_strncmp(str, "\n", ft_strlen("\n") + 1));
}

int	ft_is_redir(char *str)
{
	return (ft_is_here_doc(str)
		|| ft_is_input(str)
		|| ft_is_output(str)
		|| ft_is_append(str));
}

int	ft_is_builtin(char *str)
{
	if (!ft_strncmp(str, "echo", 5)
		|| !ft_strncmp(str, "cd", 3)
		|| !ft_strncmp(str, "pwd", 4)
		|| !ft_strncmp(str, "export", 7)
		|| !ft_strncmp(str, "unset", 6)
		|| !ft_strncmp(str, "env", 4)
		|| !ft_strncmp(str, "exit", 5))
		return (1);
	else
		return (0);
}
