/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_user_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:22:58 by mayeung           #+#    #+#             */
/*   Updated: 2024/03/06 13:20:09 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_event(void)
{
	return (0);
}

int	ft_get_user_input(void)
{
	char	*line;
	char	*old_line;
	int		parse_res;

	signal(SIGINT, &ft_signal_handler_waiting_input);
	signal(SIGQUIT, SIG_IGN);
	rl_event_hook = ft_event;
	old_line = NULL;
	parse_res = PARSE_OK;
	ft_vars()->break_readline = 0;
	line = readline(PROMPT);
	while (!ft_vars()->break_readline || parse_res == PARSE_OK)
	{
		if (!line && parse_res == PARSE_OK)
		{
			free(old_line);
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			ft_free_res(1);
			exit(ft_vars()->last_exe_res);
		}
		if (!line && parse_res == IMCOMPELETE_CMD)
			return (ft_default_signal(),
				ft_putstr_fd("unexpected EOF\n", STDERR_FILENO), PARSE_FAIL);
		if (!ft_space_only(line) || parse_res == IMCOMPELETE_CMD)
		{
			ft_trim_write_history(line);
			if (old_line)
				line = ft_free_join_str(ft_strdup("\n"), line);
			line = ft_free_join_str(old_line, line);
			if (!line)
				return (ALLOCATE_FAIL);
			ft_vars()->toklist = ft_tokenize(line);
			if (!ft_vars()->toklist)
				return (free(line), ALLOCATE_FAIL);
			parse_res = ft_parse_token(ft_vars()->toklist);
			if (parse_res == PARSE_OK || parse_res == PARSE_FAIL)
				break ;
			old_line = line;
			line = NULL;
			ft_lstclear(&ft_vars()->toklist, &ft_free_token_node);
		}
		else if (ft_space_only(line) && parse_res == PARSE_OK)
			return (ft_default_signal(), free(line), EMPTY_INPUT);
		free(line);
		line = readline(PROMPT_CON);
	}
	free(line);
	if (ft_vars()->break_readline)
	{
		parse_res = EMPTY_INPUT;
		free(old_line);
	}
	if (parse_res == PARSE_FAIL || parse_res == EMPTY_INPUT)
	{
		ft_lstclear(&ft_vars()->toklist, &ft_free_token_node);
		ft_vars()->toklist = NULL;
	}
	return (ft_default_signal(), parse_res);
}
