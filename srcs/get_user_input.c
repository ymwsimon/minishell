/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_user_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:22:58 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/26 14:23:26 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_get_user_input(char *prompt)
{
	char	*line;
	char	*old_line;
	int		parse_res;

	old_line = NULL;
	parse_res = PARSE_OK;
	line = readline(prompt);
	while (1)
	{
		if (!line && parse_res == PARSE_OK)
		{
			free(old_line);
			rl_clear_history();
			exit(0);
		}
		if (!line && parse_res == IMCOMPELETE_CMD)
			return (ft_putstr_fd("unexpected EOF", STDERR_FILENO), PARSE_FAIL);
		if (!ft_space_only(line))
		{
			ft_trim_write_history(line);
			line = ft_free_join_str(old_line, line);
		}
	}
}
