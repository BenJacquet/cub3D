/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 11:47:12 by jabenjam          #+#    #+#             */
/*   Updated: 2019/11/25 19:46:12 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list		*begin;
	t_list		*current;

	if (!lst || !f)
		return (NULL);
	begin = ft_lstnew(f(lst->content));
	current = begin;
	lst = lst->next;
	while (lst)
	{
		if (!(current->next = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&begin, (del));
			return (NULL);
		}
		lst = lst->next;
		current = current->next;
	}
	return (begin);
}
