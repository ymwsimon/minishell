/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 21:14:46 by mayeung           #+#    #+#             */
/*   Updated: 2024/01/15 00:32:48 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_redir_fds(int rfd, int wfd)
{
	dup2(rfd, STDIN_FILENO);
	dup2(wfd, STDOUT_FILENO);
}

void	ft_first_cmd(char *infile, char **arlist, int wfd, int *pfds)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd == -1)
		ft_errmsgname(CMDFOUND, arlist, infile, pfds);
	ft_redir_fds(fd, wfd);
	close(fd);
}

void	ft_last_cmd(char *outfile, char **arlist, int rfd, int *pfds)
{
	int	fd;

	fd = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd == -1)
		ft_errmsgname(CMDFOUND, arlist, outfile, pfds);
	ft_redir_fds(rfd, fd);
	close(fd);
}

void	ft_free_arlist(char **arlist)
{
	char	**tmp;

	tmp = arlist;
	while (arlist && *arlist)
	{
		free(*arlist);
		arlist++;
	}
	free(tmp);
}

pid_t	ft_run_proc(int	*pfds, int i, t_args args)
{
	char	**arlist;
	char	*cmd;
	pid_t	cpid;

	cpid = fork();
	if (!cpid)
	{
		arlist = ft_split(args.arv[i + 2], ' ');
		if (i == 0)
			ft_first_cmd(args.arv[1], arlist, pfds[1], pfds);
		else if (i == args.arc - 4)
			ft_last_cmd(args.arv[args.arc - 1], arlist, pfds[i * 2 - 2], pfds);
		else
			ft_redir_fds(pfds[i * 2 - 2], pfds[i * 2 + 1]);
		ft_close_pfds(pfds, args.arc);
		free(pfds);
		cmd = ft_getfullpath(arlist[0], NULL, args.env);
		if (!cmd)
			ft_errmsgname(CMDNOTFOUND, arlist, arlist[0], NULL);
		execve(cmd, arlist, args.env);
		free(cmd);
		ft_free_arlist(arlist);
	}
	return (cpid);
}
