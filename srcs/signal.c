/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:53:20 by mayeung           #+#    #+#             */
/*   Updated: 2024/03/06 01:04:38 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_signal_handler_waiting_input(int i)
{
	if (i == SIGINT)
	{
		ft_vars()->last_signal = 126;
		rl_done = 1;
	}
}

void	ft_signal_handler_exe_parent(int i)
{
	if (i == SIGINT)
		printf("\n");
	else if (i == SIGQUIT)
	{
		printf("\n");
		printf("Quit (core dumped)\n");
	}
}

void	ft_signal_handler_exe_child(int i)
{
	if (i == SIGINT || i == SIGQUIT)
	{
		ft_free_res(0);
		exit(127);
	}
}

void	ft_setup_signal_handler_child(void)
{
	signal(SIGINT, &ft_signal_handler_exe_child);
	signal(SIGQUIT, &ft_signal_handler_exe_child);
}

void	ft_default_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	ft_ignore_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
