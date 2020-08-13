/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 17:56:27 by jabenjam          #+#    #+#             */
/*   Updated: 2020/08/11 15:37:51 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void			swap_content(t_sprite *current, t_sprite *next)
{
	float		temp;

	temp = 0;
	if (current && next)
	{
		temp = current->x;
		current->x = next->x;
		next->x = temp;
		temp = current->y;
		current->y = next->y;
		next->y = temp;
		temp = current->dist;
		current->dist = next->dist;
		next->dist = temp;
	}
}

t_sprite		*sort_sprites(t_sprite *sprites)
{
	t_sprite	*head;
	t_sprite	*next;

	head = sprites;
	while (sprites && sprites->next)
	{
		next = sprites->next;
		if (sprites->dist < next->dist)
			swap_content(sprites, next);
		sprites = sprites->next;
	}
	return (head);
}
