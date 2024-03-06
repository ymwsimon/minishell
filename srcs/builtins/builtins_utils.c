/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 18:09:36 by mayeung           #+#    #+#             */
/*   Updated: 2024/03/06 01:24:41 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exec_builtin(char **args)
{
	if (!args)
		return (1);
	if (!ft_strncmp(args[0], "cd", 3))
		return (ft_cd(args));
	else if (!ft_strncmp(args[0], "echo", 5))
		return (ft_echo(args));
	else if (!ft_strncmp(args[0], "env", 4))
		return (ft_env(args));
	else if (!ft_strncmp(args[0], "exit", 5))
		return (ft_exit(args));
	else if (!ft_strncmp(args[0], "export", 7))
		return (ft_export(args));
	else if (!ft_strncmp(args[0], "pwd", 4))
		return (ft_pwd());
	else if (!ft_strncmp(args[0], "unset", 6))
		return (ft_unset(args));
	return (1);
}
