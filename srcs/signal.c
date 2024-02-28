/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:53:20 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/28 21:56:05 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void    ft_interrupt_handle(int i)
{
    if (i == SIGINT)
    {
        printf("\n");
        printf("minishell>>> ");
    }
}

void    ft_signal_exe_parent(int i)
{
    if (i == SIGINT)
        printf("\n");
    else if (i == SIGQUIT)
    {
        printf("\n");
        printf("Quit (core dumped)\n");
    }
}

void    ft_interrput_exe_child(int i)
{
    if (i == SIGINT)
        exit(1);
}

void    ft_default_signal(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}

void    ft_ignore_signal(void)
{
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
}