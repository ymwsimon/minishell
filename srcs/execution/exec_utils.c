/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:11:31 by luyang            #+#    #+#             */
/*   Updated: 2024/02/28 16:56:10 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_r_fd(int *original)
{
	dup2(original[0], STDIN_FILENO);
	dup2(original[1], STDOUT_FILENO);
	close(original[0]);
	close(original[1]);
}

int	ft_get_exit_status(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

int	ft_err_msg(t_err err)
{
	if (err.msg == ERR_PERM_DENIED)
		return(ft_putstr_fd("minishell: ", 2), ft_putstr_fd(err.file, 2),
			ft_putstr_fd(": Permission denied\n", 2), err.fd);
	if (err.msg == ERR_NO_SUCH_FILE)
		return (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(err.file, 2),
			ft_putstr_fd(": No such file or directory", 2), err.fd);
	return (0);
}
