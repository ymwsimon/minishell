/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:28:38 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/24 18:07:16 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(void)
{
	char	*res;

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
