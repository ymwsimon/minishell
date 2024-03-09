/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:09:06 by luyang            #+#    #+#             */
/*   Updated: 2024/03/09 20:15:33 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_here_doc(char *here_doc)
{
	int	fd;

	fd = open(here_doc, O_RDONLY);
	if (fd == -1)
		return (ft_err_msg(ft_check_read(here_doc)));
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	ft_input(char *redir)
{
	int	fd;

	if (!redir || !*redir)
		return (1);
	fd = open(redir, O_RDONLY);
	if (fd == -1)
		return (ft_err_msg(ft_check_read(redir)));
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	ft_output(char *redir)
{
	int	fd;

	if (ft_check_dir(redir, FALSE))
		return (ft_err_msg((t_err){1, ERR_IS_DIR, redir}));
	fd = open(redir, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		return (ft_err_msg(ft_check_write(redir)));
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	ft_append(char *redir)
{
	int	fd;

	if (ft_check_dir(redir, FALSE))
		return (ft_err_msg((t_err){1, ERR_IS_DIR, redir}));
	fd = open(redir, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (ft_err_msg(ft_check_write(redir)));
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}
