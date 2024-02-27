/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:53:20 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/27 19:28:10 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_interrupt_handle(int i)
{
    i += 0;
    if (i == SIGINT)
    {
        printf("\n");//minishell>>> ");
        //printf("minishell>>> ");
        //rl_redisplay();
        //printf("minishell>>> ");
        //signal(SIGINT, SIG_IGN);
        //kill(0, SIGINT);
    }
}