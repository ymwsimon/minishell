/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:28:04 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/11 18:30:47 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_push_token_to_list(t_list **list, char *str)
{
	t_token	*tok;
	t_list	*new_node;

	if (!str)
		return (0);
	tok = malloc(sizeof(t_token));
	if (!tok)
		return (free(str), 0);
	tok->str = str;
	tok->tok = RAW;
	new_node = ft_lstnew(tok);
	if (!new_node)
		return (free(tok), free(str), 0);
	ft_lstadd_back(list, new_node);
	return (1);
}

void	ft_print_enum(t_token_type tok)
{
	if (tok == RAW)
		printf("RAW");
	else if (tok == PIPE)
		printf("PIPE_|");
	else if (tok == HERE_DOC)
		printf("HERE_DOC_<<");
	else if (tok == INPUT)
		printf("INPUT_<");
	else if (tok == OUTPUT)
		printf("OUTPUT_>");
	else if (tok == APPEND)
		printf("APPEND_>>");
	else if (tok == ARG)
		printf("ARG");
	else if (tok == INFILE)
		printf("INFILE");
	else if (tok == OUTFILE)
		printf("OUTFILE");
	else if (tok == DELIMITER)
		printf("DELIMITER");
	else if (tok == OPEN_DOUBLE_QUOTE)
		printf("OPEN_DOUBLE_QUOTE");
	else if (tok == OPEN_SINGLE_QUOTE)
		printf("OPEN_SINGLE_QUOTE");
	else if (tok == AND)
		printf("AND");
	else if (tok == OR)
		printf("OR");
	else if (tok == OPEN_PAREN)
		printf("OPEN_PAREN");
	else if (tok == CLOSE_PAREN)
		printf("CLOSE_PAREN");
	else if (tok == SIMPLE_CMD)
		printf("SIMPLE_CMD");
}

void	ft_print_tokens(t_list *tokens)
{
	t_token	*t;

	printf("tokens:\n");
	while (tokens)
	{
		t = tokens->content;
		if (t->tok != SIMPLE_CMD)
			printf("data:%s tok_type:", (char *)t->str);
		else
			printf("simple cmd");
		ft_print_enum(t->tok);
		printf("\n");
		tokens = tokens->next;
	}
}

void	ft_free_token_node(void *n)
{
	t_token	*node;

	node = n;
	if (node)
	{
		free(node->str);
		free(node);
		//free cmd too
	}
}
