/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:54:13 by mayeung           #+#    #+#             */
/*   Updated: 2023/10/29 21:54:12 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*n;
	t_list	*c;

	n = 0;
	while (lst && f && del)
	{
		c = ft_lstnew(lst->content);
		c->content = f(c->content);
		ft_lstadd_back(&n, c);
		lst = lst->next;
	}
	return (n);
}
