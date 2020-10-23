/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_core_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 17:55:04 by jabenjam          #+#    #+#             */
/*   Updated: 2020/09/20 21:49:02 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_incs/cub3d_bonus.h"

t_ray_s			sprite_setup(t_var *var)
{
	t_ray_s		ray_s;
	double		x;
	double		y;

	x = var->sprites->x - (var->player.pos_x - 0.5);
	y = var->sprites->y - (var->player.pos_y - 0.5);
	ray_s.inv = 1.0 / (var->cam.plane_x * var->cam.dir_y -
			var->cam.dir_x * var->cam.plane_y);
	ray_s.x = ray_s.inv * (var->cam.dir_y * x - var->cam.dir_x * y);
	ray_s.y = ray_s.inv * (-var->cam.plane_y * x + var->cam.plane_x * y);
	ray_s.x_screen = (int)((var->width / 2) * (1 + ray_s.x / ray_s.y));
	ray_s.height = abs((int)(var->height / ray_s.y));
	ray_s.start_y = -ray_s.height / 2 + var->height / 2;
	ray_s.start_y = (ray_s.start_y < 0 ? 0 : ray_s.start_y);
	ray_s.end_y = ray_s.height / 2 + var->height / 2;
	ray_s.end_y = (ray_s.end_y >= var->height ? var->height - 1 : ray_s.end_y);
	ray_s.width = abs((int)(var->height / ray_s.y));
	ray_s.start_x = -ray_s.width / 2 + ray_s.x_screen;
	ray_s.start_x = (ray_s.start_x < 0 ? 0 : ray_s.start_x);
	ray_s.end_x = ray_s.width / 2 + ray_s.x_screen;
	ray_s.end_x = (ray_s.end_x >= var->width ? var->width - 1 : ray_s.end_x);
	return (ray_s);
}

int				raycast_sprites(t_var *var, double *zbuffer)
{
	t_sprite	*head;
	t_ray_s		ray_s;

	head = var->sprites;
	while (var->sprites)
	{
		ray_s = sprite_setup(var);
		ray_s.col = ray_s.start_x;
		while (ray_s.col < ray_s.end_x)
			sprite_x(var, &ray_s, zbuffer);
		var->sprites = var->sprites->next;
	}
	var->sprites = head;
	return (0);
}

void			get_distance(t_sprite *sprites, t_player *player)
{
	t_sprite	*head;

	head = sprites;
	while (sprites)
	{
		sprites->dist =
			((player->pos_x - sprites->x) * (player->pos_x - sprites->x) +
			(player->pos_y - sprites->y) * (player->pos_y - sprites->y));
		sprites = sprites->next;
	}
	sprites = head;
}

int				sprites_manager(t_var *var, double *zbuffer)
{
	get_distance(var->sprites, &var->player);
	var->sprites = sort_sprites(var->sprites);
	raycast_sprites(var, zbuffer);
	return (0);
}

t_sprite		*store_sprite(t_var *var, int x, int y)
{
	t_sprite	*new;

	if (!(new = malloc(sizeof(t_sprite))))
		return (NULL);
	new->x = x;
	new->y = y;
	new->dist = 0.0;
	new->next = (var->sprites ? var->sprites : NULL);
	if (var->sprites)
		new->next = var->sprites;
	var->n_sprites++;
	return (new);
}
