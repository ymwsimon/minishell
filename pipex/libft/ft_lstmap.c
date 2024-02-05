/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:54:13 by mayeung           #+#    #+#             */
/*   Updated: 2023/12/28 13:42:55 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*c;

	head = NULL;
	while (lst && f && del)
	{
		c = ft_lstnew(lst->content);
		c->content = f(c->content);
		ft_lstadd_back(&head, c);
		lst = lst->next;
	}
	return (head);
}
