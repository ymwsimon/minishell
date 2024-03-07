/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:49:47 by mayeung           #+#    #+#             */
/*   Updated: 2024/03/07 15:47:47 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	tokenize_helper2(t_list **stack, t_list **res)
{
	if (!stack || !res || !(*stack) || !(*res))
		return (1);
	if (*stack && ft_strlen((*stack)->content) == 1
		&& ft_is_double_quote((*stack)->content))
		((t_token *)ft_lstlast((*res))->content)->toktype = OPEN_DOUBLE_QUOTE;
	if (*stack && ft_strlen((*stack)->content) == 1
		&& ft_is_single_quote((*stack)->content))
		((t_token *)ft_lstlast(*res)->content)->toktype = OPEN_SINGLE_QUOTE;
	if (*stack)
		ft_lstclear(stack, &free);
	return (0);
}

int	tokenize_helper1(t_list **stack, size_t *j, size_t i, char *line)
{
	t_list	*tmp;

	if (!stack || !(*stack) || !line || !j)
		return (1);
	while (line[*j] && !ft_strrchr((*stack)->content, line[*j]))
		(*j)++;
	if ((ft_strlen((*stack)->content) != 1)
		&& (line[*j] == '\'' || line[*j] == '"'))
		ft_lstadd_front(stack, ft_lstnew(ft_substr(line, (*j)++, 1)));
	else if (line[*j])
	{
		tmp = (*stack)->next;
		ft_lstdelone(*stack, &free);
		(*stack) = tmp;
		if (i == *j && (line[*j] == '<' || line[*j] == '>'
				|| line[*j] == '&' || line[*j] == '|'
				|| line[*j] == '(' || line[*j] == ')')
			&& line[*j] == line[*j + 1])
			*j += 2;
		if (line[*j] == '"' || line[*j] == '\'')
			(*j)++;
	}
	return (0);
}

t_list	*ft_tokenize(char *line)
{
	t_list	*res;
	t_list	*stack;
	size_t	i;
	size_t	j;

	i = 0;
	res = NULL;
	stack = NULL;
	while (line && line[i])
	{
		ft_lstadd_front(&stack, ft_lstnew(ft_strdup(" |<>\"'()&;\n")));
		while (line[i] && line[i] == ' ')
			i++;
		j = i;
		while (stack && line[j])
			tokenize_helper1(&stack, &j, i, line);
		j += j == i;
		ft_push_token_to_list(&res, ft_substr(line, i, j - i));
		i = j;
		while (line[i] && line[i] == ' ')
			i++;
	}
	tokenize_helper2(&stack, &res);
	return (res);
}
