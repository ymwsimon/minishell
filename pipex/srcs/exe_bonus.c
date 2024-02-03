/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 21:17:08 by mayeung           #+#    #+#             */
/*   Updated: 2024/01/15 13:07:34 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	ft_redir_fds(int rfd, int wfd)
{
	dup2(rfd, STDIN_FILENO);
	dup2(wfd, STDOUT_FILENO);
}

void	ft_first_cmd(t_args args, char **arlist, int wfd, int *pfds)
{
	int		fd;

	if (!args.lim)
	{
		fd = open(args.arv[1], O_RDONLY);
		if (fd == -1)
			ft_errmsgname(CMDFOUND, arlist, args.arv[1], pfds);
		ft_redir_fds(fd, wfd);
		close(fd);
	}
	else
		here_doc(args, arlist, wfd, pfds);
}

void	ft_last_cmd(t_args args, char **arlist, int rfd, int *pfds)
{
	int	fd;
	int	flag;

	flag = O_WRONLY | O_TRUNC | O_CREAT;
	if (args.lim)
		flag = O_WRONLY | O_APPEND | O_CREAT;
	fd = open(args.arv[args.arc - 1], flag, 0777);
	if (fd == -1)
		ft_errmsgname(CMDFOUND, arlist, args.arv[args.arc - 1], pfds);
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
			ft_first_cmd(args, arlist, pfds[1], pfds);
		else if (i == args.arc - 4)
			ft_last_cmd(args, arlist, pfds[i * 2 - 2], pfds);
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
