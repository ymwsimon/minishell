/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:53:38 by mayeung           #+#    #+#             */
/*   Updated: 2024/03/09 21:19:44 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_res(int del_hd)
{
	ft_free_ast(&ft_vars()->ast, del_hd);
	ft_vars()->env = ft_clear_char_arr(ft_vars()->env);
	rl_clear_history();
}

char	*next_non_space(char *str)
{
	while (str && *str == ' ')
		str++;
	return (str);
}

int	parse_validate_num(char *str, int *r, int sign)
{
	if (str && *str && r)
	{
		str = next_non_space(str);
		if (*str == '-' || *str == '+')
			if (*str++ == '-')
				sign = -1;
		if (!*str || *str == ' ')
			return (0);
		while (*str && *str >= '0' && *str <= '9')
		{
			if ((sign == 1 && (*r) * 10 < 0) || (sign == -1 && (*r) * 10 > 0))
				return (0);
			*r *= 10;
			if ((sign == 1 && *r + (*str - '0') < 0) || \
				(sign == -1 && *r - (*str - '0') > 0))
				return (0);
			*r += sign * (*str - '0');
			str++;
		}
		str = next_non_space(str);
		return (!*str);
	}
	return (0);
}

int	ft_exit(char **args)
{
	int	res;

	if (!args)
		return (1);
	res = ft_vars()->last_exe_res;
	if (ft_char_arr_size(args) > 2)
	{
		printf("exit\n");
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	else if (ft_char_arr_size(args) == 2
		&& !parse_validate_num(args[1], &res, 1))
	{
		res = 2;
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	}
	printf("exit\n");
	ft_free_res(TRUE);
	exit(res);
}
