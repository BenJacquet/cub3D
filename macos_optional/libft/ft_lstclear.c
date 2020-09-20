/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 11:46:37 by jabenjam          #+#    #+#             */
/*   Updated: 2019/10/22 14:40:37 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list		*prev;
	t_list		*current;

	prev = *lst;
	current = *lst;
	if (!(*lst) || !del)
		return ;
	while (current)
	{
		prev = current;
		(*del)(prev->content);
		free(prev);
		current = current->next;
	}
	(*lst) = NULL;
}
