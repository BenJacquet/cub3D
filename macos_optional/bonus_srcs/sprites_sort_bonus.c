/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_sort_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 17:56:27 by jabenjam          #+#    #+#             */
/*   Updated: 2020/08/25 15:42:48 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_incs/cub3d_bonus.h"

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
