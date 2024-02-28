/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:53:20 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/28 18:36:13 by mayeung          ###   ########.fr       */
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

void    ft_interrupt_exe_parent(int i)
{
    if (i == SIGINT)
        printf("\n");
}

void    ft_interrput_exe_child(int i)
{
    if (i == SIGINT)
        exit(1);
}
