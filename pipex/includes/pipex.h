/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 21:18:01 by mayeung           #+#    #+#             */
/*   Updated: 2023/12/21 18:06:29 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define CMDFOUND 0
# define CMDNOTFOUND 1

# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <libft.h>

typedef struct s_args
{
	int		arc;
	char	**arv;
	char	**env;
}				t_args;

char	*ft_getfullpath(char *pname, char *res, char **env);

char	*ft_free_and_return(char *res, char **env, char *pname);

int		ft_print_usage(void);

void	ft_errmsgname(int cmdnf, char **arlist, char *fname, int *fds);

int		ft_get_exit_code(int wexit);

int		*ft_init_pipes(int arc);

void	ft_close_pfds(int *pfds, int arc);

void	ft_redir_fds(int rfd, int wfd);

void	ft_first_cmd(char *infile, char **arlist, int wfd, int *pfds);

void	ft_last_cmd(char *outfile, char **arlist, int rfd, int *pfds);

void	ft_free_arlist(char **arlist);

pid_t	ft_run_proc(int	*pfds, int i, t_args args);

#endif
