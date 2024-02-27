/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_user_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:22:58 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/27 18:25:39 by mayeung          ###   ########.fr       */
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
			ft_free_res();
			exit(0);
		}
		if (!line && parse_res == IMCOMPELETE_CMD)
			return (ft_putstr_fd("unexpected EOF ", STDERR_FILENO), PARSE_FAIL);
		if (!ft_space_only(line))
		{
			ft_trim_write_history(line);
			line = ft_free_join_str(old_line, line);
			ft_vars()->toklist = ft_tokenize(line);
			parse_res = ft_parse_token(ft_vars()->toklist);
			if (parse_res == PARSE_OK || parse_res == PARSE_FAIL)
				break ;
			old_line = line;
			line = NULL;
			ft_lstclear(&ft_vars()->toklist, &ft_free_token_node);
		}
		else if (ft_space_only(line) && parse_res == PARSE_OK)
			return (free(line), EMPTY_INPUT);
		free(line);
		line = readline("> ");
	}
	free(line);
	if (parse_res == PARSE_FAIL)
	{
		ft_lstclear(&ft_vars()->toklist, &ft_free_token_node);
		ft_vars()->toklist = NULL;
	}
	return (parse_res);
}
