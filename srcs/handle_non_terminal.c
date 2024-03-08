/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_non_terminal.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:32:30 by mayeung           #+#    #+#             */
/*   Updated: 2024/03/08 19:28:54 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_redir_file_arg(int arc, char **argv)
{
	int	fd;

	if ((arc > 1 && !argv) || !argv)
		return (INVALID_POINTER);
	if (arc > 1)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			ft_putstr_fd("Cannot open file\n", STDERR_FILENO);
			return (EXE_FAILURE);
		}
		if (dup2(fd, STDIN_FILENO) != STDIN_FILENO)
		{
			ft_putstr_fd("Redirect to file\n", STDERR_FILENO);
			return (EXE_FAILURE);
		}
		close(fd);
	}
	return (EXE_SUCCESS);
}
