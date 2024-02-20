/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:28:38 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/20 18:36:36 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(char **args)
{
	char	*res;

	if (ft_char_arr_size(args) != 1)
	{
		ft_putstr_fd("pwd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	res = getcwd(NULL, 0);
	if (!res)
	{	
		perror(NULL);
		return (1);
	}
	printf("%s\n", res);
	free(res);
	return (0);
}
