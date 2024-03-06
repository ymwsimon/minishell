/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:53:20 by mayeung           #+#    #+#             */
/*   Updated: 2024/03/06 16:51:01 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_signal_handler_waiting_input(int i)
{
	if (i == SIGINT)
	{
		ft_vars()->break_readline = 1;
		ft_vars()->last_exe_res = SIGINT_CODE;
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
		if (i == SIGINT)
			exit(SIGINT_CODE);
		else
			exit(SIGQUIT_CODE);
	}
}

int	ft_setup_signal_handler_child(int using_readline)
{
	signal(SIGINT, &ft_signal_handler_exe_child);
	if (!using_readline)
		signal(SIGQUIT, &ft_signal_handler_exe_child);
	else
		signal(SIGQUIT, SIG_IGN);
	return (0);
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
