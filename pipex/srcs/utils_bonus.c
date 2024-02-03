/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 21:17:24 by mayeung           #+#    #+#             */
/*   Updated: 2024/01/15 00:33:02 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	ft_print_usage(void)
{
	ft_putstr_fd("Need at least 4 arguments\n", STDERR_FILENO);
	ft_putstr_fd("usage: pipex infile cmd1 cmd2 ... cmdn outfile\n",
		STDERR_FILENO);
	return (1);
}

char	*ft_getfullpath(char *pname, char *res, char **env)
{
	int		i;

	i = 0;
	if (pname && ((pname[0] == '/') || pname[0] == '.'))
		return (ft_strdup(pname));
	while (env && env[i] && ft_strncmp("PATH=", env[i], ft_strlen("PATH=")))
		i++;
	if (!env || !env[i])
		return (0);
	env = ft_split(env[i] + ft_strlen("PATH="), ':');
	pname = ft_strjoin("/", pname);
	i = 0;
	while (env && env[i])
	{
		res = ft_strjoin(env[i], pname);
		if (!access(res, F_OK | X_OK))
			return (ft_free_and_return(res, env, pname));
		free(res);
		i++;
	}
	return (ft_free_and_return(NULL, env, pname));
}

char	*ft_free_and_return(char *res, char **env, char *pname)
{
	ft_free_arlist(env);
	free(pname);
	return (res);
}

void	ft_errmsgname(int cmdnf, char **arlist, char *fname, int *pfds)
{
	if (cmdnf)
		ft_putstr_fd("Command not found", STDERR_FILENO);
	else
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(fname, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	ft_free_arlist(arlist);
	free(pfds);
	if (cmdnf)
		exit(127);
	exit(1);
}

int	ft_get_exit_code(int wexit)
{
	return (wexit >> 8);
}
