/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:49:47 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/11 17:51:26 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*ft_tokenize(char *line)
{
	t_list	*res;
	t_list	*stack;
	t_list	*tmp;
	size_t	i;
	size_t	j;

	i = 0;
	res = NULL;
	stack = NULL;
	while (line && line[i])
	{
		ft_lstadd_front(&stack, ft_lstnew(ft_strdup(" |<>\"'()&")));
		while (line[i] && line[i] == ' ')
			i++;
		j = i;
		while (stack && line[j])
		{
			while (line[j] && !ft_strrchr(stack->content, line[j]))
				j++;
			if ((ft_strlen(stack->content) == 1 && ((char *)stack->content)[0] == line[j])
				|| (line[j] != '"' && line[j] != '\'' && line[j]))
			{
				tmp = stack->next;
				ft_lstdelone(stack, &free);
				stack = tmp;
				if (i == j && (line[j] == '<' || line[j] == '>' || line[j] == '&' || line[j] == '|')
					&& line[j] == line[j + 1])
					j += 2;
				if (line[j] == '"' || line[j] == '\'')
					j++;
			}
			else if (line[j])
				ft_lstadd_front(&stack, ft_lstnew(ft_substr(line, j++, 1)));
		}
		j += j == i;
		if (!ft_push_token_to_list(&res, ft_substr(line, i, j - i)))
			free(NULL); //clean up res
		i = j;
	}

	if (stack && ft_strlen(stack->content) == 1
		&& ft_is_double_quote(stack->content))
		((t_token *)ft_lstlast(res)->content)->tok = OPEN_DOUBLE_QUOTE;
	if (stack && ft_strlen(stack->content) == 1
		&& ft_is_single_quote(stack->content))
		((t_token *)ft_lstlast(res)->content)->tok = OPEN_SINGLE_QUOTE;
	if (stack)
		ft_lstclear(&stack, &free);
	//printf("stack content%s\n", (char *)stack->content);
	//ft_print_enum(((t_token *)ft_lstlast(res)->content)->tok);
	//printf("\n");
	return (res);
}