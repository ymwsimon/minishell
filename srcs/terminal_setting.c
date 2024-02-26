/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_setting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:57:21 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/26 18:36:04 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_turn_off_int_sig(void)
{
	//struct termios ter;

	//tcgetattr(STDIN_FILENO, &ter);
	//ter.c_lflag &= ~(ISIG);
	//tcsetattr(STDIN_FILENO, TCSAFLUSH, &ter);
		//tcgetattr(1, &ter);
	//ter.c_lflag |= ECHOCTL;
	//ter.c_lflag |= ICANON;t_list
	//tcsetattr(1, 0, &ter);
	signal(SIGINT, SIG_IGN);
}