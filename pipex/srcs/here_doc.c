/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 00:36:46 by mayeung           #+#    #+#             */
/*   Updated: 2024/01/15 01:04:22 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	here_doc(t_args args, char **arlist, int wfd, int *pfds)
{
	char	*line;
	char	*cmpstr;

	ft_redir_fds(STDIN_FILENO, wfd);
	ft_close_pfds(pfds, args.arc);
	free(pfds);
	ft_free_arlist(arlist);
	cmpstr = ft_strjoin(args.lim, "\n");
	line = get_next_line(STDIN_FILENO);
	while (line && ft_strncmp(line, cmpstr, ft_strlen(cmpstr) + 1))
	{
		write(STDOUT_FILENO, line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(cmpstr);
	free(line);
	exit(0);
}
