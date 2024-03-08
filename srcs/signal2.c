/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:00:25 by mayeung           #+#    #+#             */
/*   Updated: 2024/03/08 14:09:06 by mayeung          ###   ########.fr       */
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
