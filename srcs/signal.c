/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:53:20 by mayeung           #+#    #+#             */
/*   Updated: 2024/03/08 14:08:36 by mayeung          ###   ########.fr       */
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
		printf("\nQuit (core dumped)\n");
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
	if (signal(SIGINT, &ft_signal_handler_exe_child) == SIG_ERR)
		return (SIGNAL_ERROR);
	if (!using_readline)
	{
		if (signal(SIGQUIT, &ft_signal_handler_exe_child) == SIG_ERR)
			return (SIGNAL_ERROR);
	}
	else
	{
		if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			return (SIGNAL_ERROR);
	}
	return (EXE_SUCCESS);
}
