/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 21:17:18 by mayeung           #+#    #+#             */
/*   Updated: 2024/01/15 00:32:57 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	*ft_init_pipes(int arc)
{
	int	*res;
	int	i;

	res = malloc(sizeof(int) * 2 * (arc - 4));
	i = 0;
	while (i < arc - 4)
	{
		pipe(&res[i * 2]);
		i++;
	}
	return (res);
}

void	ft_close_pfds(int *pfds, int arc)
{
	int	i;

	i = 0;
	while (i < (arc - 4) * 2)
	{
		close(pfds[i]);
		i++;
	}
}

int	main(int arc, char **arv, char **env)
{
	int		*pfds;
	int		i;
	int		r;
	pid_t	id;
	t_args	args;

	if (arc != 5)
		return (ft_print_usage());
	pfds = ft_init_pipes(arc);
	args.arc = arc;
	args.arv = arv;
	args.env = env;
	i = 0;
	while (i < arc - 3)
	{
		id = ft_run_proc(pfds, i, args);
		i++;
	}
	ft_close_pfds(pfds, arc);
	free(pfds);
	waitpid(id, &r, 0);
	return (ft_get_exit_code(r));
}
