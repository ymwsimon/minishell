/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:00:25 by mayeung           #+#    #+#             */
/*   Updated: 2024/03/09 15:16:23 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_default_signal(void)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		return (SIGNAL_ERROR);
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		return (SIGNAL_ERROR);
	return (EXE_SUCCESS);
}

int	ft_ignore_signal(void)
{
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		return (SIGNAL_ERROR);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (SIGNAL_ERROR);
	return (EXE_SUCCESS);
}

int	ft_setup_signal_handler_parent(void)
{
	if (signal(SIGINT, &ft_signal_handler_exe_parent) == SIG_ERR)
		return (SIGNAL_ERROR);
	if (signal(SIGQUIT, &ft_signal_handler_exe_parent) == SIG_ERR)
		return (SIGNAL_ERROR);
	return (EXE_SUCCESS);
}
